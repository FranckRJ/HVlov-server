#pragma once

namespace hvlov
{
    /*!
     * Deleter for PImpl classes, the operator() need to be defined in each .cpp that use it (one and only one time
     * per PImpl types). Used with smart pointers.
     *
     * @tparam PimplType The type of the PImpl to delete.
     */
    template <class PimplType>
    class PimplDeleter
    {
    public:
        // TODO: Replace pointer by gsl::owner.
        /*!
         * The deleter function.
         *
         * @param ptr The pointer to delete.
         */
        void operator()(PimplType* ptr);
    };
} // namespace hvlov
