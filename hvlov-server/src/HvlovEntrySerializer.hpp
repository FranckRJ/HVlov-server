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

    private:
        /*!
         * Serialize a Folder entry to a JSON string.
         *
         * @param entry The Folder entry to serialize.
         * @return The Folder entry serialized to a JSON string.
         */
        std::string serializeEntryToJsonInternal(const entries::Folder& entry) const;

        /*!
         * Serialize a Video entry to a JSON string.
         *
         * @param entry The Video entry to serialize.
         * @return The Video entry serialized to a JSON string.
         */
        std::string serializeEntryToJsonInternal(const entries::Video& entry) const;
    };
} // namespace hvlov
