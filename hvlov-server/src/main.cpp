#include <fmt/core.h>
#include <httplib.h>
#include <memory>
#include <spdlog/spdlog.h>

#include "FileSystemLister.hpp"
#include "HvlovEntryBuilder.hpp"

int main(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::level_enum::debug);

    if (argc < 2 || argv[1][0] == '\0')
    {
        spdlog::error("Server root not passed as first param of command.");
        return 1;
    }

    const std::string serverRoot = argv[1];
    const std::string serverAddress = "localhost";
    constexpr int serverPort = 1234;

    std::unique_ptr<hvlov::IFileSystemLister> fileSystemLister = std::make_unique<hvlov::FileSystemLister>();
    hvlov::HvlovEntryBuilder::Config hvlovEntryBuilderConfig{serverRoot};
    std::unique_ptr<hvlov::IHvlovEntryBuilder> hvlovEntryBuilder =
        std::make_unique<hvlov::HvlovEntryBuilder>(hvlovEntryBuilderConfig);

    httplib::Server server;

    server.Post("/", [&](const httplib::Request& req, httplib::Response& res) {
        std::string response;
        std::vector<hvlov::HvlovEntry> entries;

        spdlog::info("Request '{}' received.", req.body);

        try
        {
            entries = hvlovEntryBuilder->buildEntriesFromFileInfos(fileSystemLister->getEntriesFromDirectory(req.body));
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

    spdlog::info("HVlov server start listening on {}:{} with '{}' as root", serverAddress, serverPort, serverRoot);
    server.listen(serverAddress.c_str(), serverPort);
}
