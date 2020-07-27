#include <filesystem>
#include <memory>

#include <spdlog/spdlog.h>

#include "FileSystemLister.hpp"
#include "Globals.hpp"
#include "HttpServerWrapper.hpp"
#include "HvlovEntryBuilder.hpp"
#include "HvlovEntrySerializer.hpp"
#include "HvlovServer.hpp"

int main(int argc, char** argv)
{
    if (hvlov::globals::buildType == "Debug")
    {
        spdlog::set_level(spdlog::level::level_enum::debug);
    }
    else
    {
        spdlog::set_level(spdlog::level::level_enum::info);
    }
    spdlog::info("HVlov-server version {}.{} launched.", hvlov::globals::versionMajor, hvlov::globals::versionMinor);

    if (argc < 2 || argv[1][0] == '\0')
    {
        spdlog::error("Server root not passed as first param of command.");
        return 1;
    }
    if (argc < 3 || argv[2][0] == '\0')
    {
        spdlog::error("Videos prefix not passed as second param of command.");
        return 1;
    }

    auto removeTrailingSlash = [](const std::filesystem::path& path) {
        return path.has_filename() ? path : path.parent_path();
    };
    const std::filesystem::path serverRoot = removeTrailingSlash(argv[1]);
    const std::filesystem::path serverVideosPrefix = removeTrailingSlash(argv[2]);
    const std::string serverAddress = "localhost";
    constexpr int serverPort = 47107;

    std::unique_ptr<hvlov::IFileSystemLister> fileSystemLister = std::make_unique<hvlov::FileSystemLister>();
    hvlov::HvlovEntryBuilder::Config hvlovEntryBuilderConfig{.serverRoot = serverRoot,
                                                             .serverVideosPrefix = serverVideosPrefix};
    std::unique_ptr<hvlov::IHvlovEntryBuilder> hvlovEntryBuilder =
        std::make_unique<hvlov::HvlovEntryBuilder>(hvlovEntryBuilderConfig);
    std::unique_ptr<hvlov::IHvlovEntrySerializer> hvlovEntrySerializer =
        std::make_unique<hvlov::HvlovEntrySerializer>();
    std::unique_ptr<hvlov::IHttpServerWrapper> httpServerWrapper = std::make_unique<hvlov::HttpServerWrapper>();

    hvlov::HvlovServer::Config hvlovServerConfig{
        .root = serverRoot, .videosUrlPrefix = serverVideosPrefix, .connectionInfo = {serverAddress, serverPort}};
    std::unique_ptr<hvlov::IHvlovServer> hvlovServer = std::make_unique<hvlov::HvlovServer>(
        hvlovServerConfig, std::move(httpServerWrapper), std::move(hvlovEntrySerializer), std::move(hvlovEntryBuilder),
        std::move(fileSystemLister));

    hvlovServer->run();
}
