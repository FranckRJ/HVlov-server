#include <filesystem>

#include <catch2/catch.hpp>

#include "HvlovEntryBuilder.hpp"

using namespace hvlov;
namespace fs = std::filesystem;

namespace
{
    const fs::path serverRoot = fs::path{"server"} / "root";
    const fs::path serverVideosPrefix = "root";
    const std::string directory1 = "folder1";
    const std::string directory2 = "folder2";
    const std::string underscoredDirectory1 = "folder_1";
    const std::string spacedDirectory1 = "folder 1";
    const std::string file1 = "video1.mp4";
    const std::string file2 = "video2.mp4";
    const std::string underscoredFile1 = "video_1.mp4";

    FileInfo createFileInfo(const fs::path& relativePath, fs::file_type type)
    {
        return FileInfo{serverRoot / relativePath, fs::file_status{type}};
    }

    HvlovEntry createHvlovFolderEntry(const std::string& fileDirectory, const std::string& fileName)
    {
        return entries::Folder{fileName, Url{fileDirectory + "/" + fileName}};
    }

    HvlovEntry createHvlovVideoEntry(const std::string& fileDirectory, const std::string& fileName)
    {
        return entries::Video{fileName, Url{serverVideosPrefix.string() + "/" + fileDirectory + "/" + fileName}};
    }
} // namespace

// NOLINTNEXTLINE
SCENARIO("HvlovEntryBuilder::buildEntriesFromFileInfos()", "[unit]")
{
    GIVEN("A constructed HvlovEntryBuilder with a valid configuration")
    {
        HvlovEntryBuilder::Config config{.serverRoot = serverRoot, .serverVideosPrefix = serverVideosPrefix};
        HvlovEntryBuilder hvlovEntryBuilder{config};

        WHEN("A valid FileInfo for a video entry is passed as argument")
        {
            FileInfo videoEntryFileInfo = createFileInfo(fs::path(directory1) / file1, fs::file_type::regular);
            std::vector<FileInfo> fileInfos{videoEntryFileInfo};

            THEN("The corresponding sorted HvlovEntry is returned")
            {
                HvlovEntry videoEntryHvlovEntry = createHvlovVideoEntry(directory1, file1);

                std::vector<HvlovEntry> expected{videoEntryHvlovEntry};
                std::vector<HvlovEntry> returnedHvlovEntries = hvlovEntryBuilder.buildEntriesFromFileInfos(fileInfos);

                REQUIRE(returnedHvlovEntries == expected);
            }
        }

        WHEN("Several valid FileInfo for video and folder entries are passed as argument")
        {
            std::vector<FileInfo> fileInfos{
                createFileInfo(fs::path(directory1) / file1, fs::file_type::regular),
                createFileInfo(fs::path(directory1) / directory2, fs::file_type::directory),
                createFileInfo(fs::path(directory1) / file2, fs::file_type::regular),
                createFileInfo(fs::path(directory1) / directory1, fs::file_type::directory)};

            THEN("The corresponding sorted HvlovEntries are returned")
            {
                std::vector<HvlovEntry> expected{
                    createHvlovFolderEntry(directory1, directory1), createHvlovFolderEntry(directory1, directory2),
                    createHvlovVideoEntry(directory1, file1), createHvlovVideoEntry(directory1, file2)};
                std::vector<HvlovEntry> returnedHvlovEntries = hvlovEntryBuilder.buildEntriesFromFileInfos(fileInfos);

                REQUIRE(returnedHvlovEntries == expected);
            }
        }

        WHEN("Two valid FileInfo for a video and folder entries with underscore in the name are passed as argument")
        {
            std::vector<FileInfo> fileInfos{
                createFileInfo(fs::path(directory1) / underscoredFile1, fs::file_type::regular),
                createFileInfo(fs::path(directory1) / underscoredDirectory1, fs::file_type::directory)};

            THEN("The corresponding sorted HvlovEntries are returned, with underscores replaced by spaces for folders")
            {
                std::vector<HvlovEntry> expected{
                    HvlovEntry{entries::Folder{spacedDirectory1, Url{directory1 + "/" + underscoredDirectory1}}},
                    createHvlovVideoEntry(directory1, underscoredFile1)};
                std::vector<HvlovEntry> returnedHvlovEntries = hvlovEntryBuilder.buildEntriesFromFileInfos(fileInfos);

                REQUIRE(returnedHvlovEntries == expected);
            }
        }

        WHEN("An valid FileInfo for a video entry with a root different from server root is passed as argument")
        {
            std::vector<FileInfo> fileInfos{FileInfo{fs::path{file1}, fs::file_status{fs::file_type::regular}}};

            THEN("The buildEntriesFromFileInfos method throws because it can't match server root with file info")
            {
                REQUIRE_THROWS(hvlovEntryBuilder.buildEntriesFromFileInfos(fileInfos));
            }
        }
    }
}
