#pragma once

#include <compare>
#include <string>

#include "Url.hpp"

namespace hvlov
{
    /*!
     * Struct containing information about an entry on an HVlov server.
     */
    struct HvlovEntry
    {
        /*!
         * The type of entry, either a Video or a Folder.
         */
        enum class Type
        {
            Folder,
            Video
        };

        //! The type of entry.
        Type type;
        //! The title of the entry, that can be displayed to the user.
        std::string title;
        //! The URL used to access that entry, relative to the root of the server.
        Url url;

        //! lhs <=> rhs operation.
        std::strong_ordering operator<=>(const HvlovEntry& other) const = default;
    };
} // namespace hvlov
