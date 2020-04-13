#include "HvlovServer.hpp"

#include <fmt/core.h>
#include <httplib/httplib.h>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <utility>

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

    void HvlovServer::run()
    {
        spdlog::info("HVlov server start listening on {}:{} with '{}' as root.", _config.connexionInfo.address,
                     _config.connexionInfo.port, _config.root.string());
        _server->listen(_config.connexionInfo.address.c_str(), _config.connexionInfo.port);
    }

    void HvlovServer::initializeRequestHandlers()
    {
        _server->Get("/", [this](const httplib::Request& req, httplib::Response& res) {
            std::string path;

            if (req.has_param("path"))
            {
                path = req.get_param_value("path");
            }

            HttpResponse response = handleListRequest(path);

            res.status = static_cast<int>(response.status);
            res.set_content(response.body, "text/plain");
        });
    }

    HttpResponse HvlovServer::handleListRequest(std::string_view path)
    {
        spdlog::info("List request for '{}' received.", path);

        std::vector<hvlov::HvlovEntry> entries;
        try
        {
            entries = _hvlovEntryBuilder->buildEntriesFromFileInfos(_fileSystemLister->getEntriesFromDirectory(path));
        }
        catch (const std::exception& e)
        {
            spdlog::error("Error while trying to get entries info of '{}' : {}.", path, e.what());
            return HttpResponse{HttpResponse::Status::BadRequest, fmt::format("Error : {}", e.what())};
        }

        std::string responseBody;
        for (const auto& entry : entries)
        {
            std::string result = fmt::format("<{0} url=\"{1}\">{2}</{0}>",
                                             (entry.type == hvlov::HvlovEntry::Type::Folder ? "folder" : "video"),
                                             entry.url.toString(), entry.title);

            spdlog::debug(result);
            responseBody += result + "\n";
        }

        spdlog::info("List request for '{}' succeed.", path);
        return HttpResponse{HttpResponse::Status::Ok, responseBody};
    }
} // namespace hvlov
