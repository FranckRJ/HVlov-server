#pragma once

#include <filesystem>
#include <memory>
#include <string_view>

#include "HttpResponse.hpp"
#include "IFileSystemLister.hpp"
#include "IHvlovEntryBuilder.hpp"
#include "IHvlovServer.hpp"
#include "ServerConnectionInfo.hpp"

// Forward declaration
namespace httplib
{
    class Server;
}

namespace hvlov
{
    class HvlovServer : public IHvlovServer
    {
    public:
        /*!
         * A configuration struct for an HvlovServer.
         */
        struct Config
        {
            //! The root directory where HvlovEntries will be retrieve.
            std::filesystem::path root;
            //! The data on what the server will listen (address + port).
            ServerConnectionInfo connectionInfo;
        };

        /*!
         * Construct an HvlovServer with a specific configuration and services.
         *
         * @param config The configuration to use.
         * @param hvlovEntryBuilder The service used to build HvlovEntries.
         * @param fileSystemLister The service used to retrieve info about files on filesystem.
         */
        explicit HvlovServer(Config config, std::unique_ptr<IHvlovEntryBuilder> hvlovEntryBuilder,
                             std::unique_ptr<IFileSystemLister> fileSystemLister);

        ~HvlovServer() override;

        void run() override;

    private:
        /*!
         * Initialize the request handlers of the server.
         */
        void initializeRequestHandlers();

        /*!
         * Handle a list request on the given path, relatively to the server root..
         * Return an HTTP response with status 200 and an HTML list of HvlovEntries in case of success.
         * Return an HTTP response with another status and a error message in case of error.
         *
         * @param pathParam The path where to execute the list, relatively to the server root.
         * @return The HTTP response of the request.
         */
        HttpResponse handleListRequest(std::string_view pathParam);

    private:
        //! The configuration of the server.
        const Config _config;

        //! The service used to build HvlovEntries.
        const std::unique_ptr<IHvlovEntryBuilder> _hvlovEntryBuilder;
        //! The service used to retrieve info about files on filesystem.
        const std::unique_ptr<IFileSystemLister> _fileSystemLister;

        //! The underlying server.
        std::unique_ptr<httplib::Server> _server;
    };
} // namespace hvlov
