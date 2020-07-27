#pragma once

#include "IHvlovEntrySerializer.hpp"

namespace hvlov
{
    /*!
     * Class used to serialize HvlovEntries to diverse type of strings.
     */
    class HvlovEntrySerializer : public IHvlovEntrySerializer
    {
    public:
        std::string serializeEntryToJson(const HvlovEntry& entry) const override;

        std::string serializeEntriesToJson(const std::vector<HvlovEntry>& entries) const override;
    };
} // namespace hvlov
