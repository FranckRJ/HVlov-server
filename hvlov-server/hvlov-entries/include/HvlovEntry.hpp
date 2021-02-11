#pragma once

#include <map>
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

        /*!
         * Struct containing information about a group of videos on an HVlov server.
         * A group of videos is several videos for the same movie, often just different qualities.
         */
        struct VideoGroup
        {
            //! The title of the video group, that can be displayed to the user.
            std::string title;
            //! A map that will map a tag to a particular URL of a video in the video group.
            std::map<std::string, Url> urls;

        private:
            //! lhs < rhs operation
            friend bool operator<(const VideoGroup& lhs, const VideoGroup& rhs)
            {
                return std::tie(lhs.title, lhs.urls) < std::tie(rhs.title, rhs.urls);
            }

            //! lhs == rhs operation
            friend bool operator==(const VideoGroup& lhs, const VideoGroup& rhs)
            {
                return std::tie(lhs.title, lhs.urls) == std::tie(rhs.title, rhs.urls);
            }

            //! lhs != rhs operation
            friend bool operator!=(const VideoGroup& lhs, const VideoGroup& rhs)
            {
                return std::tie(lhs.title, lhs.urls) != std::tie(rhs.title, rhs.urls);
            }
        };
    } // namespace entries

    using HvlovEntry = std::variant<entries::Folder, entries::Video, entries::VideoGroup>;
} // namespace hvlov
