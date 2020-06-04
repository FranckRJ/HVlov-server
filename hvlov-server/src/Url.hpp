#pragma once

#include <compare>
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

        //! lhs <=> rhs operation.
        std::strong_ordering operator<=>(const Url& other) const = default;

    private:
        //! The underlying string that store the URL.
        std::string _url;
    };
} // namespace hvlov
