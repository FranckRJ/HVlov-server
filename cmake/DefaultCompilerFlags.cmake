# Remove default MSVC warning flags because it will be set later (if asked)
if (MSVC)
    string(REPLACE "/W3" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif ()
