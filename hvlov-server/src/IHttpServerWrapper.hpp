#pragma once

#include <functional>
#include <string>

#include "BaseInterface.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

namespace hvlov
{
    /*!
     * Interface for managing an HTTP server.
     */
    class IHttpServerWrapper : public BaseInterface
    {
    public:
        //! An alias for a function that handle an HTTP request.
        using RequestHandler = std::function<HttpResponse(const HttpRequest&)>;

        /*!
         * Register an handler for a GET request to the regex "pattern" on the server.
         *
         * @param pattern A regex used to match the path of the request.
         * @param handler The function that will be called when a GET request to the given regex "pattern" is received.
         * @return The wrapper itself to be able to chain requests.
         */
        virtual IHttpServerWrapper& registerGet(const std::string& pattern, const RequestHandler& handler) = 0;

        /*!
         * Start listening on the given address and the given port. Return true if no error happened, false otherwise.
         * This function is blocking and will only return when the server stop listening.
         *
         * @param address The address where to listen.
         * @param port The port on which to listen.
         * @return True if the server was normally stopped, false if it was stopped because an error happened.
         */
        virtual bool listen(const std::string& address, int port) = 0;
    };
} // namespace hvlov
