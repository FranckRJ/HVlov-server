function(enable_coverage project_name)
    set(COMPILER_COMPATIBLE_WITH_SANITIZER FALSE)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "^(Apple)?Clang$")
        set(COMPILER_COMPATIBLE_WITH_SANITIZER TRUE)
    endif ()

    option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" OFF)
    if (ENABLE_COVERAGE)
        if (COMPILER_COMPATIBLE_WITH_SANITIZER)
            target_compile_options(${project_name} INTERFACE --coverage -O0 -g -fprofile-arcs -ftest-coverage)
            target_link_libraries(${project_name} INTERFACE --coverage)
            message(STATUS "Code coverage enabled.")
        else ()
            message(SEND_ERROR "Code coverage requested but compiler is not compatible.")
        endif ()
    else ()
        message(STATUS "Code coverage not enabled.")
    endif ()
endfunction()
