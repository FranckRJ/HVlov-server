#pragma once

#include <string>
#include <vector>

#include "BaseInterface.hpp"
#include "HvlovEntry.hpp"

namespace hvlov
{
    /*!
     * Interface used to format HvlovEntries to diverse type of strings.
     */
    class IHvlovEntryFormatter : public BaseInterface
    {
    public:
        /*!
         * Format an HvlovEntry to an HTML string.
         *
         * @param entry The HvlovEntry to format.
         * @return The HvlovEntry formatted to an HTML string.
         */
        virtual std::string formatEntryToHtml(const HvlovEntry& entry) const = 0;

        /*!
         * Format a vector of HvlovEntries to a vector of HTML strings.
         *
         * @param entries The HvlovEntries to format.
         * @return The HvlovEntries formatted to a vector of strings.
         */
        virtual std::vector<std::string> formatEntriesToHtml(const std::vector<HvlovEntry>& entries) const = 0;
    };
} // namespace hvlov
