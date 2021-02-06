#pragma once

#include <string>
#include <tuple>
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

        private:
            //! lhs < rhs operation
            friend bool operator<(const Folder& lhs, const Folder& rhs)
            {
                return std::tie(lhs.title, lhs.url) < std::tie(rhs.title, rhs.url);
            }

            //! lhs == rhs operation
            friend bool operator==(const Folder& lhs, const Folder& rhs)
            {
                return std::tie(lhs.title, lhs.url) == std::tie(rhs.title, rhs.url);
            }

            //! lhs != rhs operation
            friend bool operator!=(const Folder& lhs, const Folder& rhs)
            {
                return std::tie(lhs.title, lhs.url) != std::tie(rhs.title, rhs.url);
            }
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

        private:
            //! lhs < rhs operation
            friend bool operator<(const Video& lhs, const Video& rhs)
            {
                return std::tie(lhs.title, lhs.url) < std::tie(rhs.title, rhs.url);
            }

            //! lhs == rhs operation
            friend bool operator==(const Video& lhs, const Video& rhs)
            {
                return std::tie(lhs.title, lhs.url) == std::tie(rhs.title, rhs.url);
            }

            //! lhs != rhs operation
            friend bool operator!=(const Video& lhs, const Video& rhs)
            {
                return std::tie(lhs.title, lhs.url) != std::tie(rhs.title, rhs.url);
            }
        };
    } // namespace entries

    using HvlovEntry = std::variant<entries::Folder, entries::Video>;
} // namespace hvlov
