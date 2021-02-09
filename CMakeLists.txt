cmake_minimum_required(VERSION 3.13)

project(HVlov-server VERSION 0.2 LANGUAGES CXX)

# Set C++ standard requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/StandardProjectSettings.cmake)

# Link these 'library' to set the c++ standard / compile-time options requested
add_library(project_global_options INTERFACE)
add_library(project_exe_options INTERFACE)
add_library(project_test_options INTERFACE)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

include(cmake/FixCompilerSpecificStuff.cmake)

# Setup base compiler options
target_compile_features(project_global_options INTERFACE cxx_std_17)
target_link_libraries(project_exe_options INTERFACE project_global_options)
target_link_libraries(project_test_options INTERFACE project_global_options)

# Setup compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer / coverage options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_global_options)
include(cmake/Coverage.cmake)
enable_coverage(project_exe_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Build libraries as shared libraries" OFF)

include(cmake/Conan.cmake)
run_conan()

option(ENABLE_TESTING "Enable Test Builds" ON)
if (ENABLE_TESTING)
    enable_testing()
    message(STATUS "Building Tests.")
    add_subdirectory(tests)
endif ()

add_subdirectory(hvlov-server)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${HVlov-server_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${HVlov-server_VERSION_MINOR}")
include(CPack)
