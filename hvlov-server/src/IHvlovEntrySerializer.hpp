#pragma once

#include <string>
#include <vector>

#include "BaseInterface.hpp"
#include "HvlovEntry.hpp"

namespace hvlov
{
    /*!
     * Interface used to serialize HvlovEntries to diverse type of strings.
     */
    class IHvlovEntrySerializer : public BaseInterface
    {
    public:
        /*!
         * Serialize an HvlovEntry to a JSON string.
         *
         * @param entry The HvlovEntry to serialize.
         * @return The HvlovEntry serialized to a JSON string.
         */
        virtual std::string serializeEntryToJson(const HvlovEntry& entry) const = 0;

        /*!
         * Serialize a vector of HvlovEntries to a JSON string.
         *
         * @param entries The HvlovEntries to serialize.
         * @return The HvlovEntries serialized to a JSON string.
         */
        virtual std::string serializeEntriesToJson(const std::vector<HvlovEntry>& entries) const = 0;
    };
} // namespace hvlov
