#pragma once

#include <filesystem>
#include <vector>

#include "BaseInterface.hpp"
#include "FileInfo.hpp"

namespace hvlov
{
    /*!
     * Interface used to list entries on the file system depending on some criteria.
     */
    class IFileSystemLister : public BaseInterface
    {
    public:
        /*!
         * Return all the entries information of a given directory. Not recursive.
         *
         * @param directoryPath The directory from where to get the data.
         * @return A vector of FileInfo containing the entries information.
         */
        virtual std::vector<FileInfo> getEntriesFromDirectory(const std::filesystem::path& directoryPath) const = 0;
    };
} // namespace hvlov
