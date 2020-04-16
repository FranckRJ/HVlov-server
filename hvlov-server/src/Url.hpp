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
         * Compare two Urls.
         *
         * @param lhs Left hand side of the comparison.
         * @param rhs Right hand side of the comparison
         * @return True if they are equals, false otherwise.
         */
        friend bool operator==(const Url& lhs, const Url& rhs);

    private:
        //! The underlying string that store the URL.
        std::string _url;
    };
} // namespace hvlov
