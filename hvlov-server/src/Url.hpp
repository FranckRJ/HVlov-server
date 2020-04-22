#pragma once

#include <string>

namespace hvlov
{
    /*!
     * Class representing an URL.
     */
    class Url
    {
    public:
        /*!
         * Construct an URL from a string representation of it.
         *
         * @param url The string representation of the URL.
         */
        explicit Url(std::string url = "");

        /*!
         * Return a string representation of the URL.
         *
         * @return a string representation of the URL.
         */
        [[nodiscard]] std::string toString() const;

    private:
        /*!
         * Return the result of the spaceship operator applied to lhs and rhs, lhs <=> rhs.
         * The result is negative if lhs < rhs, positive if lhs > rhs, 0 if lhs == rhs.
         *
         * @param lhs The left hand side of the operation.
         * @param rhs The right hand side of the operation.
         * @return The result of lhs <=> rhs.
         */
        friend int operatorSpaceship(const Url& lhs, const Url& rhs);

        //! lhs == rhs operation.
        friend bool operator==(const Url& lhs, const Url& rhs);

        //! lhs != rhs operation.
        friend bool operator!=(const Url& lhs, const Url& rhs);

        //! lhs < rhs operation.
        friend bool operator<(const Url& lhs, const Url& rhs);

        //! lhs > rhs operation.
        friend bool operator>(const Url& lhs, const Url& rhs);

        //! lhs <= rhs operation.
        friend bool operator<=(const Url& lhs, const Url& rhs);

        //! lhs >= rhs operation.
        friend bool operator>=(const Url& lhs, const Url& rhs);

    private:
        //! The underlying string that store the URL.
        std::string _url;
    };
} // namespace hvlov
