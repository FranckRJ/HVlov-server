#define NANORANGE_NO_STD_FORWARD_DECLARATIONS

#include "HvlovEntryBuilder.hpp"

#include <functional>
#include <nanorange.hpp>
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
        nano::transform(fileInfos, nano::back_inserter(hvlovEntries),
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
            nano::replace(hvlovEntryTitle, '_', ' ');
        }

        return hvlovEntryTitle;
    }

    Url HvlovEntryBuilder::extractHvlovEntryUrl(const FileInfo& fileInfo) const
    {
        auto [filePathMismatch, rootPathMismatch] = nano::mismatch(fileInfo.path, _config.serverRoot);

        if (rootPathMismatch != _config.serverRoot.end() || filePathMismatch == fileInfo.path.end())
        {
            throw std::runtime_error{"Entry not inside server root."};
        }

        std::filesystem::path entryPath =
            std::accumulate(filePathMismatch, fileInfo.path.end(), std::filesystem::path{}, std::divides{});

        return Url{entryPath.generic_string()};
    }
} // namespace hvlov
