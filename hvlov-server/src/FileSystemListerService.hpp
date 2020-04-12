#pragma once

#include "IFileSystemListerService.hpp"

namespace hvlov
{
    /*!
     * Class used to list entries on the file system depending on some criteria.
     */
    class FileSystemListerService : public IFileSystemListerService
    {
    public:
        std::vector<FileInfo> getEntriesFromDirectory(const std::filesystem::path& directoryPath) override;
    };
} // namespace hvlov
