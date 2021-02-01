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
        //! The underlying string that store the URL.
        std::string _url;

    private:
        friend bool operator<(const Url& lhs, const Url& rhs)
        {
            return lhs._url < rhs._url;
        }

        friend bool operator==(const Url& lhs, const Url& rhs)
        {
            return lhs._url == rhs._url;
        }

        friend bool operator!=(const Url& lhs, const Url& rhs)
        {
            return lhs._url != rhs._url;
        }
    };
} // namespace hvlov
