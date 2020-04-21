#pragma once

#include <memory>

#include "IHttpServerWrapper.hpp"

// Forward declaration
namespace httplib
{
    class Server;
}

namespace hvlov
{
    /*!
     * Class for managing an HTTP server from the httplib library.
     */
    class HttpServerWrapper : public IHttpServerWrapper
    {
    public:
        /*!
         * Construct an HttpServerWrapper.
         */
        HttpServerWrapper();

        IHttpServerWrapper& registerGet(const std::string& pattern, const RequestHandler& handler) override;

        bool listen(const std::string& address, int port) override;

    private:
        /*!
         * Deleter for an httplib::Server. Used for unique_ptr to use the PImpl idiom.
         */
        class HttpLibServerDeleter
        {
        public:
            /*!
             * Function that delete an httplib::Server.
             *
             * @param ptr The httplib::Server that will be deleted.
             */
            void operator()(httplib::Server* ptr);
        };

        //! The underlying PImpl for the server.
        const std::unique_ptr<httplib::Server, HttpLibServerDeleter> _server;
    };
} // namespace hvlov
