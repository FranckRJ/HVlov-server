#include <catch2/catch.hpp>

#include "HvlovEntrySerializer.hpp"

using namespace hvlov;

namespace
{
    const std::string directory1 = "directory1";
    const std::string directory2 = "directory2";
    const std::string file1 = "file1";
    const std::string file2 = "file2";
    const std::string urlToDirectory1 = "url/to/" + directory1;
    const std::string urlToDirectory2 = "url/to/" + directory2;
    const std::string urlToFile1 = "url/to/" + file1;
    const std::string urlToFile2 = "url/to/" + file2;
} // namespace

// NOLINTNEXTLINE
SCENARIO("HvlovEntrySerializer::serializeEntryToJson()", "[unit]")
{
    GIVEN("A constructed HvlovEntrySerializer")
    {
        HvlovEntrySerializer hvlovEntrySerializer;

        WHEN("A video entry is serialized to JSON")
        {
            HvlovEntry videoEntry{entries::Video{file1, Url{urlToFile1}}};

            THEN("The returned string is the JSON representation of the video entry")
            {
                std::string expected = R"({"title":"file1","type":"video","url":"url/to/file1"})";

                REQUIRE(hvlovEntrySerializer.serializeEntryToJson(videoEntry) == expected);
            }
        }

        WHEN("A folder entry is serialized to JSON")
        {
            HvlovEntry folderEntry{entries::Folder{directory1, Url{urlToDirectory1}}};

            THEN("The returned string is the JSON representation of the folder entry")
            {
                std::string expected = R"({"title":"directory1","type":"folder","url":"url/to/directory1"})";

                REQUIRE(hvlovEntrySerializer.serializeEntryToJson(folderEntry) == expected);
            }
        }
    }
}

SCENARIO("HvlovEntrySerializer::serializeEntriesToJson()", "[unit]")
{
    GIVEN("A constructed HvlovEntrySerializer")
    {
        HvlovEntrySerializer hvlovEntrySerializer;

        WHEN("Several video / folder entries are serialized to JSON")
        {
            std::vector<HvlovEntry> hvlovEntries{HvlovEntry{entries::Video{file1, Url{urlToFile1}}},
                                                 HvlovEntry{entries::Folder{directory1, Url{urlToDirectory1}}},
                                                 HvlovEntry{entries::Video{file2, Url{urlToFile2}}},
                                                 HvlovEntry{entries::Folder{directory2, Url{urlToDirectory2}}}};

            THEN("The returned string is the JSON representation of each entries")
            {
                std::string expected = R"([{"title":"file1","type":"video","url":"url/to/file1"},)"
                                       R"({"title":"directory1","type":"folder","url":"url/to/directory1"},)"
                                       R"({"title":"file2","type":"video","url":"url/to/file2"},)"
                                       R"({"title":"directory2","type":"folder","url":"url/to/directory2"}])";

                REQUIRE(hvlovEntrySerializer.serializeEntriesToJson(hvlovEntries) == expected);
            }
        }
    }
}
