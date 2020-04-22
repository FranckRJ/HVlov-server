#pragma once

#include <filesystem>

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
            //! The path of the root of the server. Video entries are built relatively to it.
            std::filesystem::path serverRoot;
            //! The base directory relative to root. Folder entries are built relatively to it.
            std::filesystem::path serverRelativeBase;
        };

        /*!
         * Construct an HvlovEntryBuilder with a specific configuration.
         *
         * @param config The configuration to use.
         */
        explicit HvlovEntryBuilder(Config config);

        std::vector<HvlovEntry> buildEntriesFromFileInfos(const std::vector<FileInfo>& fileInfos) const override;

    private:
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
        HvlovEntry::Type extractHvlovEntryType(const FileInfo& fileInfo) const;

        /*!
         * Extract the HvlovEntry Title information from the parameters.
         * Apply some modification depending of the entry type to have more readable name.
         *
         * @param fileInfo The FileInfo used to extract the Title information.
         * @param hvlovEntryType The entry type used to chose which modification to do on the title.
         * @return The extracted Title information.
         */
        std::string extractHvlovEntryTitle(const FileInfo& fileInfo, HvlovEntry::Type hvlovEntryType) const;

        /*!
         * Extract the HvlovEntry URL from the parameter. It will be relative to the server root or base
         * depending on the type of entry.
         *
         * @param fileInfo The FileInfo used to extract the Url information.
         * @param hvlovEntryType The entry type used to chose which modification to do on the title.
         * @return The extracted Url information.
         */
        Url extractHvlovEntryUrl(const FileInfo& fileInfo, HvlovEntry::Type hvlovEntryType) const;

    private:
        //! The configuration of the HvlovEntryBuilder.
        const Config _config;
    };
} // namespace hvlov
