#pragma once

#include "IFileSystemLister.hpp"

namespace hvlov
{
    /*!
     * Class used to list entries on the file system depending on some criteria.
     */
    class FileSystemLister : public IFileSystemLister
    {
    public:
        std::vector<FileInfo> getEntriesFromDirectory(const std::filesystem::path& directoryPath) const override;
    };
} // namespace hvlov
