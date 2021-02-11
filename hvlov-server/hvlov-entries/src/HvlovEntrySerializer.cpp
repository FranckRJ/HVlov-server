#include "HvlovEntrySerializer.hpp"

#include <algorithm>
#include <iterator>

#include <nlohmann/json.hpp>

namespace hvlov
{
    namespace
    {
        /*!
         * Serialize a Folder into a JSON object.
         *
         * @param entry The Folder to serialize.
         * @return The resulting JSON object.
         */
        nlohmann::json serializeEntryToJsonInternal(const entries::Folder& entry)
        {
            nlohmann::json jsonEntry;

            jsonEntry["type"] = "folder";
            jsonEntry["url"] = entry.url.toString();
            jsonEntry["title"] = entry.title;

            return jsonEntry;
        }

        /*!
         * Serialize a Video into a JSON object.
         *
         * @param entry The Video to serialize.
         * @return The resulting JSON object.
         */
        nlohmann::json serializeEntryToJsonInternal(const entries::Video& entry)
        {
            nlohmann::json jsonEntry;

            jsonEntry["type"] = "video";
            jsonEntry["url"] = entry.url.toString();
            jsonEntry["title"] = entry.title;

            return jsonEntry;
        }

        /*!
         * Serialize a VideoGroup into a JSON object.
         *
         * @param entry The VideoGroup to serialize.
         * @return The resulting JSON object.
         */
        nlohmann::json serializeEntryToJsonInternal(const entries::VideoGroup& entry)
        {
            nlohmann::json jsonEntry;

            nlohmann::json jsonUrls;
            for (const auto& urlsMapElem : entry.urls)
            {
                jsonUrls[urlsMapElem.first] = urlsMapElem.second.toString();
            }

            jsonEntry["type"] = "video_group";
            jsonEntry["title"] = entry.title;
            jsonEntry["urls"] = jsonUrls;

            return jsonEntry;
        }

        /*!
         * Serialize an HvlovEntry into a JSON object.
         *
         * @param entry The HvlovEntry to serialize.
         * @return The resulting JSON object.
         */
        nlohmann::json serializeEntryToJsonInternal(const HvlovEntry& entry)
        {
            return std::visit([](const auto& genericEntry) { return serializeEntryToJsonInternal(genericEntry); },
                              entry);
        }
    } // namespace

    std::string HvlovEntrySerializer::serializeEntryToJson(const HvlovEntry& entry) const
    {
        return serializeEntryToJsonInternal(entry).dump();
    }

    std::string HvlovEntrySerializer::serializeEntriesToJson(const std::vector<HvlovEntry>& entries) const
    {
        nlohmann::json jsonEntries;

        std::transform(entries.begin(), entries.end(), std::back_inserter(jsonEntries),
                       [](const HvlovEntry& entry) { return serializeEntryToJsonInternal(entry); });

        return jsonEntries.dump();
    }
} // namespace hvlov
