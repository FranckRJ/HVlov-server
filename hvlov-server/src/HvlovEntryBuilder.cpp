#include "HvlovEntryBuilder.hpp"

#include <functional>
#include <numeric>
#include <stdexcept>
#include <utility>

#include <nanorange.hpp>

namespace hvlov
{
    HvlovEntryBuilder::HvlovEntryBuilder(HvlovEntryBuilder::Config config) : _config{std::move(config)}
    {
    }

    std::vector<HvlovEntry> HvlovEntryBuilder::buildEntriesFromFileInfos(const std::vector<FileInfo>& fileInfos) const
    {
        std::vector<HvlovEntry> hvlovEntries;

        hvlovEntries.reserve(fileInfos.size());
        nano::transform(fileInfos, nano::back_inserter(hvlovEntries),
                        [this](const auto& p) { return fileInfoToHvlovEntry(p); });

        nano::sort(hvlovEntries);

        return hvlovEntries;
    }

    HvlovEntry HvlovEntryBuilder::fileInfoToHvlovEntry(const FileInfo& fileInfo) const
    {
        HvlovEntry::Type hvlovEntryType = extractHvlovEntryType(fileInfo);
        std::string hvlovEntryTitle = extractHvlovEntryTitle(fileInfo, hvlovEntryType);
        Url hvlovEntryUrl = extractHvlovEntryUrl(fileInfo, hvlovEntryType);

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
            nano::replace(hvlovEntryTitle, '_', ' ');
        }

        return hvlovEntryTitle;
    }

    Url HvlovEntryBuilder::extractHvlovEntryUrl(const FileInfo& fileInfo, HvlovEntry::Type hvlovEntryType) const
    {
        std::filesystem::path relativeRoot =
            (hvlovEntryType == HvlovEntry::Type::Video || _config.serverRelativeBase.empty()
                 ? _config.serverRoot
                 : _config.serverRoot / _config.serverRelativeBase);

        auto [filePathMismatch, rootPathMismatch] = nano::mismatch(fileInfo.path, relativeRoot);

        if (rootPathMismatch != relativeRoot.end() || filePathMismatch == fileInfo.path.end())
        {
            throw std::runtime_error{"Entry not inside server root."};
        }

        std::filesystem::path entryPath =
            std::accumulate(filePathMismatch, fileInfo.path.end(), std::filesystem::path{}, std::divides{});

        return Url{entryPath.generic_string()};
    }
} // namespace hvlov
