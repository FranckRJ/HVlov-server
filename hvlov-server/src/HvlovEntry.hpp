#pragma once

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
            Video,
            Folder
        };

        //! The title of the entry, that can be displayed to the user.
        std::string title;
        //! The URL used to access that entry, relative to the root of the server.
        Url url;
        //! The type of entry.
        Type type;
    };
} // namespace hvlov
