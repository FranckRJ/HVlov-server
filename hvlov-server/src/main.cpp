#include <fmt/core.h>
#include <httplib.h>
#include <spdlog/spdlog.h>

#include "FileSystemListerService.hpp"

int main()
{
    spdlog::set_level(spdlog::level::level_enum::debug);

    spdlog::debug("Hello, {}!", "World");

    httplib::Server server;

    for (auto&& entry : hvlov::FileSystemListerService{}.getEntriesFromDirectory("C:")) {
        spdlog::info(entry.path.string());
    }

    spdlog::info("Hello, {}!", "World");

    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(fmt::format("Hello, from {}\n", "{fmt}"), "text/plain");
    });

    server.listen("localhost", 1234);
}
