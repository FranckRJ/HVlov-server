add_executable(hvlov-server src/main.cpp)
target_link_libraries(hvlov-server PRIVATE project_options project_warnings CONAN_PKG::fmt CONAN_PKG::spdlog)
