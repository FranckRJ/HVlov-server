#pragma once

#include <filesystem>

namespace hvlov
{
    /*!
     * A struct containing information about a file.
     */
    struct FileInfo
    {
        //! The path of the file.
        std::filesystem::path path;
        //! The status of the file.
        std::filesystem::file_status status;
    };
} // namespace hvlov
