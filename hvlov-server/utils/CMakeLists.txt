set(LIBRARY_NAME "utils")

add_library(${LIBRARY_NAME} STATIC
        include/Url.hpp
        include/FileInfo.hpp
        include/BaseInterface.hpp
        include/PimplDeleter.hpp
        include/IFileSystemLister.hpp
        include/FileSystemLister.hpp
        src/Url.cpp
        src/FileSystemLister.cpp)

target_link_libraries(${LIBRARY_NAME} PRIVATE
        project_exe_options project_warnings
        CONAN_PKG::range-v3
        CONAN_PKG::fmt
        CONAN_PKG::spdlog)

target_include_directories(${LIBRARY_NAME} PUBLIC include/)

if (ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
