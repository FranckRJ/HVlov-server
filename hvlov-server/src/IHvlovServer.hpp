#pragma once

#include "BaseInterface.hpp"

namespace hvlov
{
    /*!
     * Interface for managing an HVlov server.
     */
    class IHvlovServer : public BaseInterface
    {
    public:
        /*!
         * This function start the server and only return when the server is stopped.
         */
        virtual void run() = 0;
    };
} // namespace hvlov
