#include "HvlovEntryBuilder.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
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
        std::ranges::transform(fileInfos, std::back_inserter(hvlovEntries),
                               [this](const auto& p) { return fileInfoToHvlovEntry(p); });

        std::ranges::sort(hvlovEntries);

        return hvlovEntries;
    }

    HvlovEntry HvlovEntryBuilder::fileInfoToHvlovEntry(const FileInfo& fileInfo) const
    {
        EntryType entryType = extractHvlovEntryType(fileInfo);
        std::string entryTitle = extractHvlovEntryTitle(fileInfo, entryType);
        Url entryUrl = extractHvlovEntryUrl(fileInfo, entryType);

        switch (entryType)
        {
            case EntryType::Folder:
            {
                return entries::Folder{entryTitle, entryUrl};
            }
            case EntryType::Video:
            {
                return entries::Video{entryTitle, entryUrl};
            }
            default:
            {
                throw std::runtime_error{"Wrong entry type."};
            }
        }
    }

    HvlovEntryBuilder::EntryType HvlovEntryBuilder::extractHvlovEntryType(const FileInfo& fileInfo) const
    {
        return (fileInfo.status.type() == std::filesystem::file_type::directory ? EntryType::Folder : EntryType::Video);
    }

    std::string HvlovEntryBuilder::extractHvlovEntryTitle(const FileInfo& fileInfo, EntryType entryType) const
    {
        std::string entryTitle = fileInfo.path.filename().string();

        if (entryType == EntryType::Folder)
        {
            std::ranges::replace(entryTitle, '_', ' ');
        }

        return entryTitle;
    }

    Url HvlovEntryBuilder::extractHvlovEntryUrl(const FileInfo& fileInfo, EntryType entryType) const
    {
        auto [filePathMismatch, rootPathMismatch] = std::ranges::mismatch(fileInfo.path, _config.serverRoot);

        if (rootPathMismatch != _config.serverRoot.end() || filePathMismatch == fileInfo.path.end())
        {
            throw std::runtime_error{"Entry not inside server root."};
        }

        std::filesystem::path entryPath =
            std::accumulate(filePathMismatch, fileInfo.path.end(), std::filesystem::path{}, std::divides{});

        if (entryType == EntryType::Video && !_config.serverVideosPrefix.empty())
        {
            entryPath = _config.serverVideosPrefix / entryPath;
        }

        return Url{entryPath.generic_string()};
    }
} // namespace hvlov
