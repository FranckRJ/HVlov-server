#include <fmt/core.h>
#include <spdlog/spdlog.h>

int main()
{
    spdlog::info("Hello, {}!", "World");
    fmt::print("Hello, from {}\n", "{fmt}");
}
