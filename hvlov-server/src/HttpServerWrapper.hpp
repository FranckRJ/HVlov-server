#pragma once

#include <memory>

#include "IHttpServerWrapper.hpp"
#include "PimplDeleter.hpp"

namespace hvlov
{
    /*!
     * Class for managing an HTTP server from the httplib library.
     */
    class HttpServerWrapper : public IHttpServerWrapper
    {
    public:
        struct PrivateImpl;

    public:
        /*!
         * Construct an HttpServerWrapper.
         */
        HttpServerWrapper();

        IHttpServerWrapper& registerGet(const std::string& pattern, const RequestHandler& handler) override;

        bool listen(const std::string& address, int port) override;

    private:
        //! The underlying PImpl for the server and router.
        const std::unique_ptr<PrivateImpl, PimplDeleter<PrivateImpl>> _pimpl;
    };
} // namespace hvlov
