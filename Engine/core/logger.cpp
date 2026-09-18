#include "logger.h"
#include <spdlog/spdlog.h>

namespace Logger
{
    void Init()
    {
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
        spdlog::set_level(spdlog::level::trace);
        spdlog::info("Logger initialized");
    }
}