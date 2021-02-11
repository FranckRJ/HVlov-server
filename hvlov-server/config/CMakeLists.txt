set(LIBRARY_NAME "config")

add_library(${LIBRARY_NAME} INTERFACE)

configure_file(generated/Globals.hpp.in generated/Globals.hpp)

target_include_directories(${LIBRARY_NAME} INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/generated")
