#include "HvlovEntryBuilder.hpp"

#include <array>
#include <functional>
#include <numeric>
#include <stdexcept>
#include <utility>

#include <range/v3/all.hpp>

namespace hvlov
{
    HvlovEntryBuilder::HvlovEntryBuilder(HvlovEntryBuilder::Config config) : _config{std::move(config)}
    {}

    std::vector<HvlovEntry> HvlovEntryBuilder::buildEntriesFromFileInfos(const std::vector<FileInfo>& fileInfos) const
    {
        std::vector<HvlovEntry> hvlovEntries =
            fileInfos
            | ranges::views::transform([this](const auto& fileInfo) { return fileInfoToHvlovEntry(fileInfo); })
            | ranges::to_vector;

        ranges::sort(hvlovEntries);

        regroupCompatiblesVideos(hvlovEntries);

        return hvlovEntries;
    }

    void HvlovEntryBuilder::regroupCompatiblesVideos(std::vector<HvlovEntry>& hvlovEntries) const
    {
        for (std::size_t i = 0; i < hvlovEntries.size(); ++i)
        {
            if (std::holds_alternative<entries::Video>(hvlovEntries[i]))
            {
                regroupVideoAtIndexIfPossible(hvlovEntries, i);
            }
        }
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
            ranges::replace(entryTitle, '_', ' ');
        }

        return entryTitle;
    }

    Url HvlovEntryBuilder::extractHvlovEntryUrl(const FileInfo& fileInfo, EntryType entryType) const
    {
        auto [filePathMismatch, rootPathMismatch] = ranges::mismatch(fileInfo.path, _config.serverRoot);

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

    auto HvlovEntryBuilder::getVideoGroupElemInfo(const Url& url) const -> std::optional<VideoGroupElemInfo>
    {
        namespace fs = std::filesystem;

        constexpr static std::array validTags{".usd", ".sd", ".md", ".hd", ".uhd"};

        fs::path urlAsPath = url.toPath();
        fs::path ext = urlAsPath.extension();
        fs::path genericName = urlAsPath.stem();
        fs::path tag = genericName.extension();
        genericName.replace_extension(ext);

        if (ext.empty() || genericName.empty() || ranges::find(validTags, tag) == validTags.end())
        {
            return {};
        }
        else
        {
            VideoGroupElemInfo videoGroupElemInfo;
            videoGroupElemInfo.url = url;
            videoGroupElemInfo.genericTitle = genericName.generic_string();
            videoGroupElemInfo.tag = tag.generic_string().substr(1);

            return videoGroupElemInfo;
        }
    }

    auto HvlovEntryBuilder::buildCompatiblesIndexedVideosElemInfoViewFromHvlovEntries(
        const std::vector<HvlovEntry>& hvlovEntries, std::size_t index,
        const VideoGroupElemInfo& mainVideoElemInfo) const
    {
        namespace views = ranges::views;

        return hvlovEntries             //
               | views::enumerate       //
               | views::drop(index + 1) //
               | views::filter([](const auto& indexedEntry)
                               { return std::holds_alternative<entries::Video>(indexedEntry.second); }) //
               | views::transform(
                   [](const auto& indexedVideo)
                   { return std::make_pair(indexedVideo.first, std::get<entries::Video>(indexedVideo.second).url); }) //
               | views::transform(
                   [this](const auto& indexedVideoUrl)
                   { return std::make_pair(indexedVideoUrl.first, getVideoGroupElemInfo(indexedVideoUrl.second)); }) //
               | views::filter([](const auto& indexedVideoElemInfoOpt)
                               { return indexedVideoElemInfoOpt.second.has_value(); }) //
               | views::transform(
                   [](const auto& indexedVideoElemInfoOpt)
                   { return std::make_pair(indexedVideoElemInfoOpt.first, indexedVideoElemInfoOpt.second.value()); }) //
               | views::filter([&mainVideoElemInfo](const auto& indexedVideoElemInfo)
                               { return indexedVideoElemInfo.second.genericTitle == mainVideoElemInfo.genericTitle; });
    }

    void HvlovEntryBuilder::regroupVideoAtIndexIfPossible(std::vector<HvlovEntry>& hvlovEntries,
                                                          std::size_t index) const
    {
        std::optional<VideoGroupElemInfo> mainVideoElemInfoOpt =
            getVideoGroupElemInfo(std::get<entries::Video>(hvlovEntries[index]).url);

        if (!mainVideoElemInfoOpt)
        {
            return;
        }

        VideoGroupElemInfo mainVideoElemInfo = std::move(mainVideoElemInfoOpt).value();

        auto compatiblesIndexedVideosElemInfoView =
            buildCompatiblesIndexedVideosElemInfoViewFromHvlovEntries(hvlovEntries, index, mainVideoElemInfo);

        entries::VideoGroup videoGroupEntry;
        videoGroupEntry.title = mainVideoElemInfo.genericTitle;
        videoGroupEntry.urls[mainVideoElemInfo.tag] = mainVideoElemInfo.url;

        auto compatiblesIndexedVideosElemInfo =
            compatiblesIndexedVideosElemInfoView | ranges::views::reverse | ranges::to_vector;
        for (const auto& compatiblesIndexedVideoElemInfo : compatiblesIndexedVideosElemInfo)
        {
            videoGroupEntry.urls[compatiblesIndexedVideoElemInfo.second.tag] =
                compatiblesIndexedVideoElemInfo.second.url;
            hvlovEntries.erase(std::next(hvlovEntries.begin(), compatiblesIndexedVideoElemInfo.first));
        }

        hvlovEntries[index] = std::move(videoGroupEntry);
    }
} // namespace hvlov
