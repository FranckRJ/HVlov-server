#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string_view>

#include "HttpResponse.hpp"
#include "IFileSystemLister.hpp"
#include "IHttpServerWrapper.hpp"
#include "IHvlovEntryBuilder.hpp"
#include "IHvlovEntryFormatter.hpp"
#include "IHvlovServer.hpp"
#include "ServerConnectionInfo.hpp"

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
            //! The base directory relative to root, base used for every requests.
            std::filesystem::path relativeBase;
            //! The data on what the server will listen (address + port).
            ServerConnectionInfo connectionInfo;
        };

        /*!
         * Construct an HvlovServer with a specific configuration and services.
         *
         * @param config The configuration to use.
         * @param hvlovEntryFormatter The service used to format HvlovEntries.
         * @param serverWrapper The server wrapper to use.
         * @param hvlovEntryBuilder The service used to build HvlovEntries.
         * @param fileSystemLister The service used to retrieve info about files on filesystem.
         */
        explicit HvlovServer(Config config, std::unique_ptr<IHttpServerWrapper> serverWrapper,
                             std::unique_ptr<IHvlovEntryFormatter> hvlovEntryFormatter,
                             std::unique_ptr<IHvlovEntryBuilder> hvlovEntryBuilder,
                             std::unique_ptr<IFileSystemLister> fileSystemLister);

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

        /*!
         * Check if the given path is a valid path for a request.
         * A valid path is a relative path that doesn't contain any dot or dot-dot files.
         *
         * @param path The path to check.
         * @return An empty optional in case of success, an HttpResponse containing the error in case of error.
         */
        std::optional<HttpResponse> checkPathForRequest(const std::filesystem::path& path);

    private:
        //! The configuration of the server.
        const Config _config;

        //! The underlying server.
        const std::unique_ptr<IHttpServerWrapper> _serverWrapper;
        //! The service used to format HvlovEntries.
        const std::unique_ptr<IHvlovEntryFormatter> _hvlovEntryFormatter;
        //! The service used to build HvlovEntries.
        const std::unique_ptr<IHvlovEntryBuilder> _hvlovEntryBuilder;
        //! The service used to retrieve info about files on filesystem.
        const std::unique_ptr<IFileSystemLister> _fileSystemLister;
    };
} // namespace hvlov
