#include "Url.hpp"

#include <utility>

namespace hvlov
{
    Url::Url(std::string url) : _url{std::move(url)}
    {}

    std::string Url::toString() const
    {
        return _url;
    }

    std::filesystem::path Url::toPath() const
    {
        return _url;
    }
} // namespace hvlov
