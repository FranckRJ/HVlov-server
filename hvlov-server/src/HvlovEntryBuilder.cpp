#include "HvlovEntryBuilder.hpp"

#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <utility>

namespace hvlov
{
    HvlovEntryBuilder::HvlovEntryBuilder(HvlovEntryBuilder::Config config) : _config{std::move(config)}
    {
    }

    std::vector<HvlovEntry> HvlovEntryBuilder::buildEntriesFromFileInfos(const std::vector<FileInfo>& fileInfos) const
    {
        std::vector<HvlovEntry> hvlovEntries;

        hvlovEntries.reserve(fileInfos.size());
        std::transform(fileInfos.cbegin(), fileInfos.cend(), std::back_inserter(hvlovEntries),
                       [this](const auto& p) { return fileInfoToHvlovEntry(p); });

        return hvlovEntries;
    }

    HvlovEntry HvlovEntryBuilder::fileInfoToHvlovEntry(const FileInfo& fileInfo) const
    {
        HvlovEntry::Type hvlovEntryType = extractHvlovEntryType(fileInfo);
        std::string hvlovEntryTitle = extractHvlovEntryTitle(fileInfo, hvlovEntryType);
        Url hvlovEntryUrl = extractHvlovEntryUrl(fileInfo);

        return HvlovEntry{hvlovEntryTitle, hvlovEntryUrl, hvlovEntryType};
    }

    HvlovEntry::Type HvlovEntryBuilder::extractHvlovEntryType(const FileInfo& fileInfo) const
    {
        return (fileInfo.status.type() == std::filesystem::file_type::directory ? HvlovEntry::Type::Folder
                                                                                : HvlovEntry::Type::Video);
    }

    std::string HvlovEntryBuilder::extractHvlovEntryTitle(const FileInfo& fileInfo,
                                                          HvlovEntry::Type hvlovEntryType) const
    {
        std::string hvlovEntryTitle = fileInfo.path.filename().string();

        if (hvlovEntryType == HvlovEntry::Type::Folder)
        {
            std::replace(hvlovEntryTitle.begin(), hvlovEntryTitle.end(), '_', ' ');
        }

        return hvlovEntryTitle;
    }

    Url HvlovEntryBuilder::extractHvlovEntryUrl(const FileInfo& fileInfo) const
    {
        auto pathMismatchPair = std::mismatch(fileInfo.path.begin(), fileInfo.path.end(), _config.serverRoot.begin(),
                                              _config.serverRoot.end());

        if (pathMismatchPair.second != _config.serverRoot.end() || pathMismatchPair.first == fileInfo.path.end())
        {
            throw std::runtime_error{"Entry not inside server root."};
        }

        std::filesystem::path entryPath =
            std::accumulate(pathMismatchPair.first, fileInfo.path.end(), std::filesystem::path{}, std::divides{});

        return Url{entryPath.generic_string()};
    }
} // namespace hvlov
