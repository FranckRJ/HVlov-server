#include <catch2/catch.hpp>

#include <filesystem>

#include "HvlovEntryBuilder.hpp"

using namespace hvlov;
namespace fs = std::filesystem;

SCENARIO("HvlovEntryBuilder::buildEntriesFromFileInfos()", "[unit]")
{
    GIVEN("A constructed HvlovEntryBuilder with a valid configuration")
    {
        fs::path serverRoot = fs::path{"server"} / "root";
        HvlovEntryBuilder::Config config{serverRoot};
        HvlovEntryBuilder hvlovEntryBuilder{config};

        WHEN("A valid FileInfo for a video entry is passed as argument")
        {
            std::string fileDirectory = "folder";
            std::string fileName = "video.mp4";
            FileInfo videoEntryFileInfo{serverRoot / fileDirectory / fileName, fs::file_status{fs::file_type::regular}};
            std::vector<FileInfo> fileInfos{videoEntryFileInfo};

            THEN("The corresponding HvlovEntry is returned")
            {
                HvlovEntry videoEntryHvlovEntry{fileName, Url{fileDirectory + "/" + fileName}, HvlovEntry::Type::Video};

                std::vector<HvlovEntry> returnedHvlovEntries = hvlovEntryBuilder.buildEntriesFromFileInfos(fileInfos);

                REQUIRE(returnedHvlovEntries.size() == 1);
                REQUIRE(returnedHvlovEntries.at(0).title == videoEntryHvlovEntry.title);
                REQUIRE(returnedHvlovEntries.at(0).url == videoEntryHvlovEntry.url);
                REQUIRE(returnedHvlovEntries.at(0).type == videoEntryHvlovEntry.type);
            }
        }
    }
}
