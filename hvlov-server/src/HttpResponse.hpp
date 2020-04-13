#pragma once

#include <string>

namespace hvlov
{
    /*!
     * A struct representing an HTTP response.
     */
    struct HttpResponse
    {
        /*!
         * An enum for HTTP status.
         */
        enum class Status
        {
            Ok = 200,
            BadRequest = 400,
            InternalServerError = 500,
        };

        //! The status of the response.
        Status status;
        //! The body of the response.
        std::string body;
    };
} // namespace hvlov
