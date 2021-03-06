# Remove default MSVC warning flags because it will be set later (if asked)
if (MSVC)
    string(REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif ()

# Link ws2_32 for Windows with GCC (required for cpp-httplib)
if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(project_global_options INTERFACE ws2_32)
    message(STATUS "Added ws2_32 library because Windows with GCC was detected.")
endif ()

# Link stdc++fs for GCC 8 (required)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND
        CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8 AND
        CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
    target_link_libraries(project_global_options INTERFACE stdc++fs)
    message(STATUS "Added stdc++fs library because GCC 8 was detected.")
endif ()
