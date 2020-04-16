#pragma once

#include <string>

namespace hvlov
{
    /*!
     * Struct holding information to connect to a server.
     */
    struct ServerConnectionInfo
    {
        //! The address on which the server listen.
        std::string address;
        //! The port on which the server listen.
        int port;
    };
} // namespace hvlov
