#pragma once

#include "IHvlovEntryFormatter.hpp"

namespace hvlov
{
    /*!
     * Class used to format HvlovEntries to diverse type of strings.
     */
    class HvlovEntryFormatter : public IHvlovEntryFormatter
    {
    public:
        std::string formatEntryToHtml(const HvlovEntry& entry) const override;

        std::vector<std::string> formatEntriesToHtml(const std::vector<HvlovEntry>& entries) const override;
    };
} // namespace hvlov
