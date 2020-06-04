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
} // namespace hvlov
