#include <fmt/core.h>
#include <httplib.h>
#include <spdlog/spdlog.h>

int main()
{
    spdlog::info("Hello, {}!", "World");

    httplib::Server server;

    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content(fmt::format("Hello, from {}\n", "{fmt}"), "text/plain");
    });

    server.listen("localhost", 1234);
}
