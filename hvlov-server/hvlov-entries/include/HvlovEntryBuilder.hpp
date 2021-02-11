#pragma once

#include <filesystem>
#include <optional>

#include "IHvlovEntryBuilder.hpp"

namespace hvlov
{
    /*!
     * Class for building HvlovEntries relatively to a server root.
     */
    class HvlovEntryBuilder : public IHvlovEntryBuilder
    {
    public:
        /*!
         * A configuration struct for an HvlovEntryBuilder.
         */
        struct Config
        {
            //! The path of the root of the server. Entries are built relatively to it.
            std::filesystem::path serverRoot;
            //! A prefix appended to video entry URL, because they are not accessed from root.
            std::filesystem::path serverVideosPrefix;
        };

        /*!
         * Construct an HvlovEntryBuilder with a specific configuration.
         *
         * @param config The configuration to use.
         */
        explicit HvlovEntryBuilder(Config config);

        std::vector<HvlovEntry> buildEntriesFromFileInfos(const std::vector<FileInfo>& fileInfos) const override;

    private:
        /*
         * Type of an HvlovEntry, only used during parsing.
         */
        enum class EntryType
        {
            Folder,
            Video
        };

        /*
         * Info about an element of a VideoGroup entry.
         */
        struct VideoGroupElemInfo
        {
            //! The URL to the element.
            Url url;
            //! The generic title of the entry, it's the name of the file without the tag.
            std::string genericTitle;
            //! The tag of the element, it's a piece of string that define its specificities in the VideoGroup.
            std::string tag;
        };

    private:
        /*!
         * Update the given hvlovEntries by regrouping compatibles videos (multiple url pointing to different versions
         * of the same video).
         *
         * @param hvlovEntries The list of HvlovEntry to update.
         */
        void regroupCompatiblesVideos(std::vector<HvlovEntry>& hvlovEntries) const;

        /*!
         * Create an HvlovEntry from a FileInfo, relatively to the server root.
         *
         * @param fileInfo The FileInfo that will be used to create the HvlovEntry.
         * @return The created HvlovEntry.
         */
        HvlovEntry fileInfoToHvlovEntry(const FileInfo& fileInfo) const;

        /*!
         * Extract the HvlovEntry Type information from the parameters.
         *
         * @param fileInfo The FileInfo used to extract the Type information.
         * @return The extracted Type information.
         */
        EntryType extractHvlovEntryType(const FileInfo& fileInfo) const;

        /*!
         * Extract the HvlovEntry Title information from the parameters.
         * Apply some modification depending of the entry type to have more readable name.
         *
         * @param fileInfo The FileInfo used to extract the Title information.
         * @param entryType The entry type used to chose which modification to do on the title.
         * @return The extracted Title information.
         */
        std::string extractHvlovEntryTitle(const FileInfo& fileInfo, EntryType entryType) const;

        /*!
         * Extract the HvlovEntry URL from the parameter. It will be relative to the server root or base
         * depending on the type of entry.
         *
         * @param fileInfo The FileInfo used to extract the Url information.
         * @param entryType The entry type used to chose which modification to do on the url.
         * @return The extracted Url information.
         */
        Url extractHvlovEntryUrl(const FileInfo& fileInfo, EntryType entryType) const;

        /*!
         * Return the VideoGroupElemInfo for the given URL, if the URL doesn't link to a VideoGroup, return an empty
         * optional.
         *
         * @param url The URL to use for building the VideoGroupElemInfo.
         * @return An optional containing a VideoGroupElemInfo if the url link to a VideoGroup, or an empty optional
         *         otherwise.
         */
        std::optional<VideoGroupElemInfo> getVideoGroupElemInfo(const Url& url) const;

        /*!
         * Build a view that will contains every element compatibles with the given VideoGroup represented by the
         * parameters. This view will contains pairs consisting of the index of the entry in the vector of HvlovEntries
         * and a VideoGroupElemInfo built from the compatible entry.
         *
         * @param hvlovEntries The vector containing all the entries.
         * @param index The index at which the first VideoGroup element was found.
         * @param mainVideoElemInfo The VideoGroupElemInfo of the first element of the VideoGroup.
         * @return A view of pairs consisting of the index of the entry in the vector of HvlovEntries and a
         *         VideoGroupElemInfo built from the compatible entry.
         */
        auto
        buildCompatiblesIndexedVideosElemInfoViewFromHvlovEntries(const std::vector<HvlovEntry>& hvlovEntries,
                                                                  std::size_t index,
                                                                  const VideoGroupElemInfo& mainVideoElemInfo) const;

        /*!
         * The function will modify the given vector of HVlovEntry by forming a VideoGroup of all the videos that are of
         * the same group as the video at position index if it's possible. If it's not possible (no VideoGroup could be
         * formed) the vector will be untouched.
         * If the VideoGroup was formed, the entry at index will be replaced by that VideoGroup and every Video entry
         * used for building that VideoGroup is removed from the vector.
         *
         * @param hvlovEntries The vector of HVlovEntry to mutate for (possibly) creating a new VideoGroup.
         * @param index The index at which the first element of the VideoGroup is present.
         */
        void regroupVideoAtIndexIfPossible(std::vector<HvlovEntry>& hvlovEntries, std::size_t index) const;

    private:
        //! The configuration of the HvlovEntryBuilder.
        const Config _config;
    };
} // namespace hvlov
