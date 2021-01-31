#pragma once

#include <compare>
#include <string>
#include <variant>

#include "Url.hpp"

namespace hvlov
{
    namespace entries
    {
        /*!
         * Struct containing information about a folder on an HVlov server.
         */
        struct Folder
        {
            //! The title of the folder, that can be displayed to the user.
            std::string title;
            //! The URL used to access the folder, relative to the root of the server.
            Url url;

            //! lhs <=> rhs operation.
            std::strong_ordering operator<=>(const Folder& other) const = default;
        };

        /*!
         * Struct containing information about a video on an HVlov server.
         */
        struct Video
        {
            //! The title of the video, that can be displayed to the user.
            std::string title;
            //! The URL used to access the video, relative to the root of the server.
            Url url;

            //! lhs <=> rhs operation.
            std::strong_ordering operator<=>(const Video& other) const = default;
        };
    } // namespace entries

    using HvlovEntry = std::variant<entries::Folder, entries::Video>;
} // namespace hvlov
