set(LIBRARY_NAME "hvlov-entries")

add_library(${LIBRARY_NAME} STATIC
        include/HvlovEntry.hpp
        include/IHvlovEntryBuilder.hpp
        include/IHvlovEntrySerializer.hpp
        include/HvlovEntryBuilder.hpp
        include/HvlovEntrySerializer.hpp
        src/HvlovEntryBuilder.cpp
        src/HvlovEntrySerializer.cpp)

target_link_libraries(${LIBRARY_NAME} PRIVATE
        project_exe_options project_warnings
        CONAN_PKG::range-v3
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::nlohmann_json
        PUBLIC
        utils)

target_include_directories(${LIBRARY_NAME} PUBLIC include/)

if (ENABLE_TESTING)
    add_subdirectory(tests)
endif ()
