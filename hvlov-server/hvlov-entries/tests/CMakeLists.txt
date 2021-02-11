set(TESTED_LIB "hvlov-entries")
set(TESTS_NAME "tests-${TESTED_LIB}")

# automatically enable catch2 to generate ctest targets
if (CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else ()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif ()

add_executable(${TESTS_NAME}
        src/main.cpp
        src/TestHvlovEntryBuilder.cpp
        src/TestHvlovEntrySerializer.cpp)

target_link_libraries(${TESTS_NAME} PRIVATE
        project_test_options project_warnings
        ${TESTED_LIB}
        CONAN_PKG::catch2)

catch_discover_tests(${TESTS_NAME})
