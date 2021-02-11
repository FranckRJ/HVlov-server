set(LIBRARY_NAME "lib-hvlov-server")

add_library(${LIBRARY_NAME} STATIC
        include/HttpRequest.hpp
        include/HttpResponse.hpp
        include/ServerConnectionInfo.hpp
        include/IHttpServerWrapper.hpp
        include/IHvlovServer.hpp
        include/HttpServerWrapper.hpp
        include/HvlovServer.hpp
        src/HttpServerWrapper.cpp
        src/HvlovServer.cpp)

target_link_libraries(${LIBRARY_NAME} PRIVATE
        project_exe_options project_warnings
        CONAN_PKG::range-v3
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::cpp-httplib
        PUBLIC
        hvlov-entries
        utils)

target_include_directories(${LIBRARY_NAME} PUBLIC include/)
