add_library(lib-hvlov-server STATIC
        src/FileSystemLister.cpp
        src/FileSystemLister.hpp
        src/IFileSystemLister.hpp
        src/FileInfo.hpp
        src/HvlovEntry.hpp
        src/Url.hpp
        src/Url.cpp
        src/IHvlovEntryBuilder.hpp
        src/HvlovEntryBuilder.cpp
        src/HvlovEntryBuilder.hpp
        src/BaseInterface.hpp
        src/ServerConnectionInfo.hpp
        src/IHvlovServer.hpp
        src/HvlovServer.cpp
        src/HvlovServer.hpp
        src/HttpResponse.hpp
        src/IHttpServerWrapper.hpp
        src/HttpServerWrapper.cpp
        src/HttpServerWrapper.hpp
        src/HttpRequest.hpp
        src/IHvlovEntryFormatter.hpp
        src/HvlovEntryFormatter.cpp
        src/HvlovEntryFormatter.hpp
        src/PimplDeleter.hpp)

configure_file(generated/Globals.hpp.in generated/Globals.hpp)

target_link_libraries(lib-hvlov-server PRIVATE
        project_exe_options project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::cpp-httplib)

target_include_directories(lib-hvlov-server PUBLIC src/ "${CMAKE_CURRENT_BINARY_DIR}/generated")

add_executable(hvlov-server src/main.cpp)

target_link_libraries(hvlov-server PRIVATE
        project_exe_options project_warnings
        lib-hvlov-server
        CONAN_PKG::spdlog)

install(TARGETS hvlov-server DESTINATION bin)
