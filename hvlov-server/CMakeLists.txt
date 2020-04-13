add_executable(hvlov-server
        src/main.cpp
        src/FileSystemLister.cpp
        src/FileSystemLister.hpp
        src/IFileSystemLister.hpp
        src/FileInfo.hpp
        src/BaseInterface.hpp)

target_link_libraries(hvlov-server PRIVATE
        project_options project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::cpp-httplib)
