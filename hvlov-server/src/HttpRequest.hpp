#pragma once

#include <map>
#include <string>

namespace hvlov
{
    /*!
     * A struct representing an HTTP request.
     */
    struct HttpRequest
    {
        //! The parameters of the request.
        std::multimap<std::string, std::string> params;
    };
} // namespace hvlov
