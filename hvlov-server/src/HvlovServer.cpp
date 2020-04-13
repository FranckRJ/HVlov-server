#include "HvlovServer.hpp"

#include <fmt/core.h>
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
    {
        if (!_hvlovEntryBuilder || !_fileSystemLister)
        {
            throw std::invalid_argument{"HvlovServer cannot be initialized with null parameters."};
        }

        initializeRequestHandlers();
    }

    void HvlovServer::initializeRequestHandlers()
    {
        _server.Post("/", [this](const httplib::Request& req, httplib::Response& res) {
            std::string response;
            std::vector<hvlov::HvlovEntry> entries;

            spdlog::info("List request for '{}' received.", req.body);

            try
            {
                entries =
                    _hvlovEntryBuilder->buildEntriesFromFileInfos(_fileSystemLister->getEntriesFromDirectory(req.body));
            }
            catch (const std::exception& e)
            {
                spdlog::error("Error while trying to get entries info of '{}' : {}.", req.body, e.what());
                res.set_content(fmt::format("Error : {}", e.what()), "text/plain");
                return;
            }

            for (auto&& entry : entries)
            {
                std::string result = fmt::format("<{0} url=\"{1}\">{2}</{0}>",
                                                 (entry.type == hvlov::HvlovEntry::Type::Folder ? "folder" : "video"),
                                                 entry.url.toString(), entry.title);

                spdlog::debug(result);
                response += result + "\n";
            }

            res.set_content(response, "text/plain");
        });
    }

    void HvlovServer::run()
    {
        spdlog::info("HVlov server start listening on {}:{} with '{}' as root.", _config.connexionInfo.address,
                     _config.connexionInfo.port, _config.root.string());
        _server.listen(_config.connexionInfo.address.c_str(), _config.connexionInfo.port);
    }
} // namespace hvlov
