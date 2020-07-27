#include "HvlovEntrySerializer.hpp"

#include <algorithm>
#include <iterator>
#include <ranges>

#include <fmt/core.h>

namespace hvlov
{
    std::string HvlovEntrySerializer::serializeEntryToJson(const HvlovEntry& entry) const
    {
        return fmt::format(R"({{"type":"{0}","url":"{1}","title":"{2}"}})",
                           (entry.type == HvlovEntry::Type::Folder ? "folder" : "video"), entry.url.toString(),
                           entry.title);
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
} // namespace hvlov
