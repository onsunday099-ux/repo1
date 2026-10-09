#define MINIAUDIO_IMPLEMENTATION
#include "audio.h"
#include <iostream>

namespace audio {

    Audio::Audio() : isInitialized(false) {
        // ให้ Engine::Init() เป็นคนเรียก Init() เพียงที่เดียว
    }

    Audio::~Audio() {
        Shutdown();
    }

    bool Audio::Init() {
        if (isInitialized) return true;

        result = ma_engine_init(NULL, &engine);
        if (result != MA_SUCCESS) {
            std::cerr << "[Audio] Failed to initialize audio engine.\n";
            return false;
        }

        isInitialized = true;
        return true;
    }

    void Audio::Play(std::string filepath) {
        if (!isInitialized) {
            std::cerr << "[Audio] Cannot play sound, engine not initialized.\n";
            return;
        }

        // ถ้ายังไม่เคยโหลดไฟล์นี้เข้ามา
        if (sounds.find(filepath) == sounds.end()) {
            auto newSound = std::make_unique<ma_sound>();

            result = ma_sound_init_from_file(&engine, filepath.c_str(), 0, NULL, NULL, newSound.get());

            // ⚠️ จุดสำคัญที่สุด: ถ้าโหลดไฟล์ไม่สำเร็จ ต้อง return ทันที ห้ามสั่ง start!
            if (result != MA_SUCCESS) {
                std::cerr << "[Audio] Failed to load sound file (file not found or wrong path): " << filepath << "\n";
                return;
            }

            sounds[filepath] = std::move(newSound);
        }

        ma_sound_start(sounds[filepath].get());
    }

    void Audio::Stop(std::string filepath) {
        if (!isInitialized) return;

        auto it = sounds.find(filepath);
        if (it != sounds.end()) {
            ma_sound_stop(it->second.get());
        }
    }

    void Audio::Shutdown() {
        if (isInitialized) {
            for (auto& pair : sounds) {
                if (pair.second) {
                    ma_sound_uninit(pair.second.get());
                }
            }
            sounds.clear();
            ma_engine_uninit(&engine);
            isInitialized = false;
        }
    }

}