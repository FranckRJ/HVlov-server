#include "HvlovServer.hpp"

#include <stdexcept>
#include <utility>

#include <fmt/core.h>
#include <httplib/httplib.h>
#include <nanorange.hpp>
#include <spdlog/spdlog.h>

namespace hvlov
{
    HvlovServer::HvlovServer(HvlovServer::Config config, std::unique_ptr<IHvlovEntryBuilder> hvlovEntryBuilder,
                             std::unique_ptr<IFileSystemLister> fileSystemLister)
        : _config{std::move(config)}
        , _hvlovEntryBuilder{std::move(hvlovEntryBuilder)}
        , _fileSystemLister{std::move(fileSystemLister)}
        , _server{std::make_unique<httplib::Server>()}
    {
        if (!_hvlovEntryBuilder || !_fileSystemLister)
        {
            throw std::invalid_argument{"HvlovServer cannot be initialized with null parameters."};
        }

        initializeRequestHandlers();
    }

    HvlovServer::~HvlovServer() = default;

    void HvlovServer::run()
    {
        spdlog::info("HVlov server start listening on {}:{} with '{}' as root.", _config.connectionInfo.address,
                     _config.connectionInfo.port, _config.root.string());
        _server->listen(_config.connectionInfo.address.c_str(), _config.connectionInfo.port);
    }

    void HvlovServer::initializeRequestHandlers()
    {
        _server->Get("/", [this](const httplib::Request& req, httplib::Response& res) {
            std::string pathParam;

            if (req.has_param("path"))
            {
                pathParam = req.get_param_value("path");
            }

            HttpResponse response = handleListRequest(pathParam);

            res.status = static_cast<int>(response.status);
            res.set_content(response.body, "text/plain");
        });
    }

    HttpResponse HvlovServer::handleListRequest(std::string_view pathParam)
    {
        spdlog::info("List request for '{}' received.", pathParam);

        std::filesystem::path listPath = pathParam;
        listPath.make_preferred();

        // is_relative is not reliable because it could be relative to root (instead of relative to anything).
        if (listPath.has_root_path())
        {
            std::string errorMessage = fmt::format("Error: path '{}' isn't relative.", pathParam);

            spdlog::error(errorMessage);
            return HttpResponse{HttpResponse::Status::BadRequest, errorMessage};
        }

        if (nano::any_of(listPath, [](const auto& subPath) { return subPath == ".." || subPath == "."; }))
        {
            std::string errorMessage =
                fmt::format("Error: path '{}' contains dot or dot-dot file, which is invalid.", pathParam);

            spdlog::error(errorMessage);
            return HttpResponse{HttpResponse::Status::BadRequest, errorMessage};
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

        std::string responseBody;
        for (const auto& entry : entries)
        {
            std::string result =
                fmt::format("<{0} url=\"{1}\">{2}</{0}>", (entry.type == HvlovEntry::Type::Folder ? "folder" : "video"),
                            entry.url.toString(), entry.title);

            spdlog::debug(result);
            responseBody += result + "\n";
        }

        spdlog::info("List request for '{}' succeed.", pathParam);
        return HttpResponse{HttpResponse::Status::Ok, responseBody};
    }
} // namespace hvlov
