set(EXECUTABLE_NAME "hvlov-server")

add_executable(${EXECUTABLE_NAME} src/main.cpp)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        project_exe_options project_warnings
        CONAN_PKG::range-v3
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        lib-hvlov-server
        config)

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
