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

    int operatorSpaceship(const Url& lhs, const Url& rhs)
    {
        if (lhs._url != rhs._url)
        {
            return (lhs._url < rhs._url ? -1 : 1);
        }

        return 0;
    }

    bool operator==(const Url& lhs, const Url& rhs)
    {
        return (operatorSpaceship(lhs, rhs) == 0);
    }

    bool operator!=(const Url& lhs, const Url& rhs)
    {
        return (operatorSpaceship(lhs, rhs) != 0);
    }

    bool operator<(const Url& lhs, const Url& rhs)
    {
        return (operatorSpaceship(lhs, rhs) < 0);
    }

    bool operator>(const Url& lhs, const Url& rhs)
    {
        return (operatorSpaceship(lhs, rhs) > 0);
    }

    bool operator<=(const Url& lhs, const Url& rhs)
    {
        return (operatorSpaceship(lhs, rhs) <= 0);
    }

    bool operator>=(const Url& lhs, const Url& rhs)
    {
        return (operatorSpaceship(lhs, rhs) >= 0);
    }
} // namespace hvlov
