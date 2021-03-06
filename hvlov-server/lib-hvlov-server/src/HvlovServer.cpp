#include "HvlovServer.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

#include <fmt/core.h>
#include <range/v3/all.hpp>
#include <spdlog/spdlog.h>

namespace hvlov
{
    HvlovServer::HvlovServer(HvlovServer::Config config, std::unique_ptr<IHttpServerWrapper> serverWrapper,
                             std::unique_ptr<IHvlovEntrySerializer> hvlovEntrySerializer,
                             std::unique_ptr<IHvlovEntryBuilder> hvlovEntryBuilder,
                             std::unique_ptr<IFileSystemLister> fileSystemLister)
        : _config{std::move(config)}
        , _serverWrapper{std::move(serverWrapper)}
        , _hvlovEntrySerializer{std::move(hvlovEntrySerializer)}
        , _hvlovEntryBuilder{std::move(hvlovEntryBuilder)}
        , _fileSystemLister{std::move(fileSystemLister)}
    {
        if (!_serverWrapper || !_hvlovEntrySerializer || !_hvlovEntryBuilder || !_fileSystemLister)
        {
            throw std::invalid_argument{"HvlovServer cannot be initialized with null parameters."};
        }

        initializeRequestHandlers();
    }

    void HvlovServer::run()
    {
        spdlog::info("HVlov server start listening on {}:{} with '{}' as root and '{}' as videos URL prefix.",
                     _config.connectionInfo.address, _config.connectionInfo.port, _config.root.string(),
                     _config.videosUrlPrefix.string());
        _serverWrapper->listen(_config.connectionInfo.address, _config.connectionInfo.port);
    }

    void HvlovServer::initializeRequestHandlers()
    {
        _serverWrapper->registerGet("/",
                                    [this](const HttpRequest& req)
                                    {
                                        std::string pathParam;

                                        if (auto pathIte = req.params.find("path"); pathIte != req.params.end())
                                        {
                                            pathParam = pathIte->second;
                                        }

                                        return handleListRequest(pathParam);
                                    });
    }

    HttpResponse HvlovServer::handleListRequest(std::string_view pathParam)
    {
        spdlog::info("List request for '{}' received.", pathParam);

        std::filesystem::path listPath = pathParam;
        listPath.make_preferred();

        if (auto optionalError = checkPathForRequest(listPath); optionalError.has_value())
        {
            return *optionalError;
        }

        listPath = _config.root / listPath;
        spdlog::info("Absolute path '{}' used.", listPath.string());

        std::vector<HvlovEntry> entries;
        try
        {
            entries =
                _hvlovEntryBuilder->buildEntriesFromFileInfos(_fileSystemLister->getEntriesFromDirectory(listPath));
        }
        catch (const std::exception& e)
        {
            spdlog::error("Error while trying to get entries info of '{}' : {}.", pathParam, e.what());
            return HttpResponse{HttpResponse::Status::BadRequest, fmt::format("Error : {}", e.what())};
        }

        std::string responseBody = _hvlovEntrySerializer->serializeEntriesToJson(entries);
        spdlog::debug(responseBody);

        spdlog::info("List request for '{}' succeed.", pathParam);
        return HttpResponse{HttpResponse::Status::Ok, responseBody};
    }

    std::optional<HttpResponse> HvlovServer::checkPathForRequest(const std::filesystem::path& path)
    {
        // is_relative is not reliable because it could be relative to root (instead of relative to anything).
        if (path.has_root_path())
        {
            std::string errorMessage = fmt::format("Error: path '{}' isn't relative.", path.generic_string());

            spdlog::error(errorMessage);
            return HttpResponse{HttpResponse::Status::BadRequest, errorMessage};
        }

        if (ranges::any_of(path, [](const auto& subPath) { return subPath == ".." || subPath == "."; }))
        {
            std::string errorMessage =
                fmt::format("Error: path '{}' contains dot or dot-dot file, which is invalid.", path.generic_string());

            spdlog::error(errorMessage);
            return HttpResponse{HttpResponse::Status::BadRequest, errorMessage};
        }

        return std::nullopt;
    }
} // namespace hvlov
