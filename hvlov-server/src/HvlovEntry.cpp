#include "HvlovEntry.hpp"

namespace hvlov
{
    int operatorSpaceship(const HvlovEntry& lhs, const HvlovEntry& rhs)
    {
        if (static_cast<int>(lhs.type) != static_cast<int>(rhs.type))
        {
            return (static_cast<int>(lhs.type) > static_cast<int>(rhs.type) ? -1 : 1);
        }

        if (lhs.title != rhs.title)
        {
            return (lhs.title < rhs.title ? -1 : 1);
        }

        if (lhs.url != rhs.url)
        {
            return (lhs.url < rhs.url ? -1 : 1);
        }

        return 0;
    }

    bool operator==(const HvlovEntry& lhs, const HvlovEntry& rhs)
    {
        return (operatorSpaceship(lhs, rhs) == 0);
    }

    bool operator!=(const HvlovEntry& lhs, const HvlovEntry& rhs)
    {
        return (operatorSpaceship(lhs, rhs) != 0);
    }

    bool operator<(const HvlovEntry& lhs, const HvlovEntry& rhs)
    {
        return (operatorSpaceship(lhs, rhs) < 0);
    }

    bool operator>(const HvlovEntry& lhs, const HvlovEntry& rhs)
    {
        return (operatorSpaceship(lhs, rhs) > 0);
    }

    bool operator<=(const HvlovEntry& lhs, const HvlovEntry& rhs)
    {
        return (operatorSpaceship(lhs, rhs) <= 0);
    }

    bool operator>=(const HvlovEntry& lhs, const HvlovEntry& rhs)
    {
        return (operatorSpaceship(lhs, rhs) >= 0);
    }
} // namespace hvlov
