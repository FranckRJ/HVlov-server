#include "FileSystemListerService.hpp"

namespace hvlov
{
    std::vector<FileInfo>
    hvlov::FileSystemListerService::getEntriesFromDirectory(const std::filesystem::path& directoryPath)
    {
        std::vector<FileInfo> entries;

        for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
        {
            entries.emplace_back(FileInfo{entry.path(), entry.status()});
        }

        return entries;
    }
} // namespace hvlov
