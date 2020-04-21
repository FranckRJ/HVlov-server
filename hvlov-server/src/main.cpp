#include <memory>

#include <spdlog/spdlog.h>

#include "FileSystemLister.hpp"
#include "HvlovEntryBuilder.hpp"
#include "HvlovServer.hpp"

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

    hvlov::HvlovServer::Config hvlovServerConfig{serverRoot, {serverAddress, serverPort}};
    std::unique_ptr<hvlov::IHvlovServer> hvlovServer = std::make_unique<hvlov::HvlovServer>(
        hvlovServerConfig, std::move(hvlovEntryBuilder), std::move(fileSystemLister));

    hvlovServer->run();
}
