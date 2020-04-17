# automatically enable catch2 to generate ctest targets
if (CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else ()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif ()

add_executable(test-hvlov-server
        src/main.cpp
        src/TestHvlovEntryBuilder.cpp)

target_link_libraries(test-hvlov-server PRIVATE
        project_test_options project_warnings
        lib-hvlov-server
        CONAN_PKG::catch2)

catch_discover_tests(test-hvlov-server
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=tests.xml)
