#pragma once

namespace hvlov
{
    /*!
     * Class defining base methods for interfaces.
     * That means a defaulted virtual destructor, all others special member functions are deleted.
     */
    class BaseInterface
    {
    public:
        virtual ~BaseInterface() = default;
        BaseInterface() = default;
        BaseInterface(const BaseInterface&) = delete;
        BaseInterface(BaseInterface&&) = delete;
        BaseInterface& operator=(const BaseInterface&) = delete;
        BaseInterface& operator=(BaseInterface&&) = delete;
    };
} // namespace hvlov
