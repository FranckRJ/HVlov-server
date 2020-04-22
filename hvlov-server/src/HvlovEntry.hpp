#pragma once

#include <string>

#include "Url.hpp"

namespace hvlov
{
    /*!
     * Struct containing information about an entry on an HVlov server.
     */
    struct HvlovEntry
    {
        /*!
         * The type of entry, either a Video or a Folder.
         */
        enum class Type
        {
            Video,
            Folder
        };

        //! The title of the entry, that can be displayed to the user.
        std::string title;
        //! The URL used to access that entry, relative to the root of the server.
        Url url;
        //! The type of entry.
        Type type;

    private:
        /*!
         * Return the result of the spaceship operator applied to lhs and rhs, lhs <=> rhs.
         * The result is negative if lhs < rhs, positive if lhs > rhs, 0 if lhs == rhs.
         *
         * @param lhs The left hand side of the operation.
         * @param rhs The right hand side of the operation.
         * @return The result of lhs <=> rhs.
         */
        friend int operatorSpaceship(const HvlovEntry& lhs, const HvlovEntry& rhs);

        //! lhs == rhs operation.
        friend bool operator==(const HvlovEntry& lhs, const HvlovEntry& rhs);

        //! lhs != rhs operation.
        friend bool operator!=(const HvlovEntry& lhs, const HvlovEntry& rhs);

        //! lhs < rhs operation.
        friend bool operator<(const HvlovEntry& lhs, const HvlovEntry& rhs);

        //! lhs > rhs operation.
        friend bool operator>(const HvlovEntry& lhs, const HvlovEntry& rhs);

        //! lhs <= rhs operation.
        friend bool operator<=(const HvlovEntry& lhs, const HvlovEntry& rhs);

        //! lhs >= rhs operation.
        friend bool operator>=(const HvlovEntry& lhs, const HvlovEntry& rhs);
    };
} // namespace hvlov
