#include "Url.hpp"

#include <utility>

namespace hvlov
{
    Url::Url(std::string url) : _url{std::move(url)}
    {
    }

    [[nodiscard]] std::string Url::toString() const
    {
        return _url;
    }

    bool operator==(const Url& lhs, const Url& rhs)
    {
        return lhs._url == rhs._url;
    }

    bool operator!=(const Url& lhs, const Url& rhs)
    {
        return !(lhs == rhs);
    }
} // namespace hvlov
