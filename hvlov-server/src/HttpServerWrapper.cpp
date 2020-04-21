#include "HttpServerWrapper.hpp"

#include <httplib/httplib.h>

namespace hvlov
{
    HttpServerWrapper::HttpServerWrapper() : _server{new httplib::Server{}}
    {
    }

    IHttpServerWrapper& HttpServerWrapper::registerGet(const std::string& pattern, const RequestHandler& handler)
    {
        _server->Get(pattern.c_str(), [handler](const httplib::Request& libReq, httplib::Response& libRes) {
            HttpRequest request{libReq.params};
            HttpResponse response = handler(request);

            libRes.status = static_cast<int>(response.status);
            libRes.set_content(response.body, "text/plain");
        });

        return *this;
    }

    bool HttpServerWrapper::listen(const std::string& address, int port)
    {
        return _server->listen(address.c_str(), port);
    }

    // TODO: Replace pointer by gsl::owner, and re-enable the cppcoreguidelines-owning-memory warning.
    void HttpServerWrapper::HttpLibServerDeleter::operator()(httplib::Server* ptr)
    {
        delete ptr;
    }
} // namespace hvlov
