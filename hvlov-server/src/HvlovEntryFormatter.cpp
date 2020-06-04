#include "HvlovEntryFormatter.hpp"

#include <algorithm>
#include <iterator>

#include <fmt/core.h>

namespace hvlov
{
    std::string HvlovEntryFormatter::formatEntryToHtml(const HvlovEntry& entry) const
    {
        return fmt::format(R"(<{0} url="{1}">{2}</{0}>)", (entry.type == HvlovEntry::Type::Folder ? "folder" : "video"),
                           entry.url.toString(), entry.title);
    }

    std::vector<std::string> HvlovEntryFormatter::formatEntriesToHtml(const std::vector<HvlovEntry>& entries) const
    {
        std::vector<std::string> formattedEntries;

        formattedEntries.reserve(entries.size());
        std::ranges::transform(entries, std::back_inserter(formattedEntries),
                               [this](const auto& p) { return formatEntryToHtml(p); });

        return formattedEntries;
    }
} // namespace hvlov
