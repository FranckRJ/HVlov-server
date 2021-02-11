#pragma once

#include <vector>

#include "BaseInterface.hpp"
#include "FileInfo.hpp"
#include "HvlovEntry.hpp"

namespace hvlov
{
    /*!
     * Interface for building HvlovEntries.
     */
    class IHvlovEntryBuilder : public BaseInterface
    {
    public:
        /*!
         * Build a vector of HvlovEntries from a vector of FileInfos. The order and size may not be the same.
         *
         * @param fileInfos The FileInfos that will be used to build the HvlovEntries.
         * @return The list of built HvlovEntries.
         */
        virtual std::vector<HvlovEntry> buildEntriesFromFileInfos(const std::vector<FileInfo>& fileInfos) const = 0;
    };
} // namespace hvlov
