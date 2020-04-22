#include <catch2/catch.hpp>

#include "HvlovEntryFormatter.hpp"

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

SCENARIO("HvlovEntryFormatter::formatEntryToHtml()", "[unit]")
{
    GIVEN("A constructed HvlovEntryFormatter")
    {
        HvlovEntryFormatter hvlovEntryFormatter;

        WHEN("A video entry is formatted to HTML")
        {
            HvlovEntry videoEntry{file1, Url{urlToFile1}, HvlovEntry::Type::Video};

            THEN("The returned string is the HTML representation of the video entry")
            {
                std::string expected = R"(<video url="url/to/file1">file1</video>)";

                REQUIRE(hvlovEntryFormatter.formatEntryToHtml(videoEntry) == expected);
            }
        }

        WHEN("A folder entry is formatted to HTML")
        {
            HvlovEntry folderEntry{directory1, Url{urlToDirectory1}, HvlovEntry::Type::Folder};

            THEN("The returned string is the HTML representation of the folder entry")
            {
                std::string expected = R"(<folder url="url/to/directory1">directory1</folder>)";

                REQUIRE(hvlovEntryFormatter.formatEntryToHtml(folderEntry) == expected);
            }
        }
    }
}

SCENARIO("HvlovEntryFormatter::formatEntriesToHtml()", "[unit]")
{
    GIVEN("A constructed HvlovEntryFormatter")
    {
        HvlovEntryFormatter hvlovEntryFormatter;

        WHEN("Several video / folder entries are formatted to HTML")
        {
            std::vector<HvlovEntry> hvlovEntries{
                HvlovEntry{file1, Url{urlToFile1}, HvlovEntry::Type::Video},
                HvlovEntry{directory1, Url{urlToDirectory1}, HvlovEntry::Type::Folder},
                HvlovEntry{file2, Url{urlToFile2}, HvlovEntry::Type::Video},
                HvlovEntry{directory2, Url{urlToDirectory2}, HvlovEntry::Type::Folder}};

            THEN("The returned strings are the HTML representation of each entries")
            {
                std::vector<std::string> expected = {R"(<video url="url/to/file1">file1</video>)",
                                                     R"(<folder url="url/to/directory1">directory1</folder>)",
                                                     R"(<video url="url/to/file2">file2</video>)",
                                                     R"(<folder url="url/to/directory2">directory2</folder>)"};

                REQUIRE(hvlovEntryFormatter.formatEntriesToHtml(hvlovEntries) == expected);
            }
        }
    }
}
