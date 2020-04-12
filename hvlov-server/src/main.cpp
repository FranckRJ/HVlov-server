#include <fmt/core.h>
#include <httplib.h>
#include <memory>
#include <spdlog/spdlog.h>

#include "FileSystemLister.hpp"

int main()
{
    const std::string serverAddress = "localhost";
    constexpr int serverPort = 1234;

    spdlog::set_level(spdlog::level::level_enum::debug);

    std::unique_ptr<hvlov::IFileSystemLister> fileSystemLister = std::make_unique<hvlov::FileSystemLister>();

    httplib::Server server;

    server.Post("/", [&](const httplib::Request& req, httplib::Response& res) {
        std::string response;
        std::vector<hvlov::FileInfo> entries;

        try
        {
            entries = fileSystemLister->getEntriesFromDirectory(req.body);
        }
        catch (const std::exception& e)
        {
            spdlog::error("Error while trying to get entries info of '{}' : {}.", req.body, e.what());
            res.set_content(fmt::format("Error : {}", e.what()), "text/plain");
            return;
        }

        for (auto&& entry : entries)
        {
            spdlog::debug(entry.path.string());
            response += entry.path.string() + "\n";
        }

        res.set_content(response, "text/plain");
    });

    spdlog::info("HVlov server start listening on {}:{}", serverAddress, serverPort);
    server.listen(serverAddress.c_str(), serverPort);
}
