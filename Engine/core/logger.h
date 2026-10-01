#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace logger {

    class Logger
    {
    public:
        static void SetLevel(int level);
    };

    void PrintLevel();
    void CreateLogFile();
    
}