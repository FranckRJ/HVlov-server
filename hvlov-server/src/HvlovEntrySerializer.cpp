#include "HvlovEntrySerializer.hpp"

#include <algorithm>
#include <iterator>
#include <ranges>

#include <fmt/core.h>
#include <nlohmann/json.hpp>

namespace hvlov
{
    std::string HvlovEntrySerializer::serializeEntryToJson(const HvlovEntry& entry) const
    {
        return std::visit([this](const auto& genericEntry) { return serializeEntryToJsonInternal(genericEntry); },
                          entry);
    }

    std::string HvlovEntrySerializer::serializeEntriesToJson(const std::vector<HvlovEntry>& entries) const
    {
        std::vector<std::string> serializedEntries;
        serializedEntries.emplace_back("[");
        std::ranges::transform(entries, std::back_inserter(serializedEntries),
                               [this](const HvlovEntry& entry) { return serializeEntryToJson(entry) + ','; });

        if (serializedEntries.back().ends_with(','))
        {
            serializedEntries.back().pop_back();
        }

        serializedEntries.emplace_back("]");

        auto entriesJoiner = serializedEntries | std::views::join;
        std::string joinedSerializedEntries(entriesJoiner.begin(), entriesJoiner.end());

        return joinedSerializedEntries;
    }

    std::string HvlovEntrySerializer::serializeEntryToJsonInternal(const entries::Folder& entry) const
    {
        nlohmann::json jsonEntry;

        jsonEntry["type"] = "folder";
        jsonEntry["url"] = entry.url.toString();
        jsonEntry["title"] = entry.title;

        return jsonEntry.dump();
    }

    std::string HvlovEntrySerializer::serializeEntryToJsonInternal(const entries::Video& entry) const
    {
        nlohmann::json jsonEntry;

        jsonEntry["type"] = "video";
        jsonEntry["url"] = entry.url.toString();
        jsonEntry["title"] = entry.title;

        return jsonEntry.dump();
    }
} // namespace hvlov
