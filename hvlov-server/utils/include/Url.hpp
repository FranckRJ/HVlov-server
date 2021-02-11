#pragma once

#include <filesystem>
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
        std::string toString() const;

        /*!
         * Return a path representation of the URL.
         *
         * @return the path representation of the URL.
         */
        std::filesystem::path toPath() const;

    private:
        //! The underlying string that store the URL.
        std::string _url;

    private:
        //! lhs < rhs operation
        friend bool operator<(const Url& lhs, const Url& rhs)
        {
            return lhs._url < rhs._url;
        }

        //! lhs == rhs operation
        friend bool operator==(const Url& lhs, const Url& rhs)
        {
            return lhs._url == rhs._url;
        }

        //! lhs != rhs operation
        friend bool operator!=(const Url& lhs, const Url& rhs)
        {
            return lhs._url != rhs._url;
        }
    };
} // namespace hvlov
