#include "HttpServerWrapper.hpp"

#include <httplib/httplib.h>

namespace hvlov
{
    /*!
     * Pimpl of HttpServerWrapper, holding private data.
     */
    struct HttpServerWrapper::PrivateImpl
    {
        //! The underlying server used for the requests.
        httplib::Server server;
    };

    template <>
    void PimplDeleter<HttpServerWrapper::PrivateImpl>::operator()(HttpServerWrapper::PrivateImpl* ptr)
    {
        delete ptr;
    }

    HttpServerWrapper::HttpServerWrapper() : _pimpl{new HttpServerWrapper::PrivateImpl}
    {
    }

    IHttpServerWrapper& HttpServerWrapper::registerGet(const std::string& pattern, const RequestHandler& handler)
    {
        _pimpl->server.Get(pattern.c_str(), [handler](const httplib::Request& libReq, httplib::Response& libRes) {
            HttpRequest request{libReq.params};
            HttpResponse response = handler(request);

            libRes.status = static_cast<int>(response.status);
            libRes.set_content(response.body, "text/plain");
        });

        return *this;
    }

    bool HttpServerWrapper::listen(const std::string& address, int port)
    {
        return _pimpl->server.listen(address.c_str(), port);
    }
} // namespace hvlov
