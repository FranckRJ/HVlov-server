#include "HvlovEntrySerializer.hpp"

#include <algorithm>
#include <iterator>

#include <nlohmann/json.hpp>

namespace hvlov
{
    namespace
    {
        nlohmann::json serializeEntryToJsonInternal(const entries::Folder& entry)
        {
            nlohmann::json jsonEntry;

            jsonEntry["type"] = "folder";
            jsonEntry["url"] = entry.url.toString();
            jsonEntry["title"] = entry.title;

            return jsonEntry;
        }

        nlohmann::json serializeEntryToJsonInternal(const entries::Video& entry)
        {
            nlohmann::json jsonEntry;

            jsonEntry["type"] = "video";
            jsonEntry["url"] = entry.url.toString();
            jsonEntry["title"] = entry.title;

            return jsonEntry;
        }

        nlohmann::json serializeEntryToJsonInternal(const HvlovEntry& entry)
        {
            return std::visit([](const auto& genericEntry) { return serializeEntryToJsonInternal(genericEntry); },
                              entry);
        }
    } // namespace

    std::string HvlovEntrySerializer::serializeEntryToJson(const HvlovEntry& entry) const
    {
        return serializeEntryToJsonInternal(entry).dump();
    }

    std::string HvlovEntrySerializer::serializeEntriesToJson(const std::vector<HvlovEntry>& entries) const
    {
        nlohmann::json jsonEntries;

        std::transform(entries.begin(), entries.end(), std::back_inserter(jsonEntries),
                       [](const HvlovEntry& entry) { return serializeEntryToJsonInternal(entry); });

        return jsonEntries.dump();
    }
} // namespace hvlov
