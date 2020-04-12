add_executable(hvlov-server
        src/main.cpp
        src/FileSystemListerService.cpp
        src/FileSystemListerService.hpp
        src/IFileSystemListerService.hpp
        src/FileInfo.hpp)

target_link_libraries(hvlov-server PRIVATE
        project_options project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::cpp-httplib)
