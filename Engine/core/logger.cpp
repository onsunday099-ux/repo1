#include "logger.h"

#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>

namespace logger {

    // 1. Implementation ของฟังก์ชัน static ในคลาส Logger
    void Logger::SetLevel(int level)
    {
        // แปลง int เป็น spdlog::level::level_enum (0 = trace, 1 = debug, 2 = info, ...)
        spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
    }

    // 2. Implementation ของ PrintLevel (ป้องกัน LNK2019 หากถูกเรียกใช้)
    void PrintLevel()
    {
        spdlog::info("Current log level: {}", static_cast<int>(spdlog::get_level()));
    }

    // 3. Implementation ของ CreateLogFile
    void CreateLogFile()
    {
        try
        {
            // สร้างโฟลเดอร์ logs หากยังไม่มี
            std::filesystem::create_directories("logs");

            // Sink สำหรับ Console
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::trace);

            // Sink สำหรับเขียนลงไฟล์
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                "logs/game.log",
                1024 * 1024 * 5, // 5 MB
                2,               // 2 backup files
                true             // rotate_on_open
            );
            file_sink->set_level(spdlog::level::trace);

            // รวม Sink ทั้งสองตัว
            std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
            auto combined_logger = std::make_shared<spdlog::logger>("engine_logger", sinks.begin(), sinks.end());

            combined_logger->set_level(spdlog::level::trace);
            spdlog::set_default_logger(combined_logger);

            spdlog::info("Log Started");
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cerr << "Log init failed: " << ex.what() << '\n';
        }
    }

}