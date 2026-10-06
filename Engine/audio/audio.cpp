#include "audio.h"
#include <iostream>

namespace audio {
	Audio::Audio() {
		Audio::Init();
		isInitialized = false;
	}

	Audio::~Audio() {
		if (isInitialized) {
			for (auto& pair : sounds) {
				ma_sound_uninit(&pair.second);
			}
			sounds.clear();
			ma_engine_uninit(&engine);
		}		
	}

	bool Audio::Init() {

		result = ma_engine_init(NULL, &engine);
		if (result != MA_SUCCESS) {
			printf("Failed to initialize audio engine.\n");
			return false;
		}
		isInitialized = true;
		return true;
	}

	void Audio::Play(std::string filepath) {
		if (!isInitialized) return;

		if (sounds.find(filepath) == sounds.end()) {
			ma_sound newSound;
			result = ma_sound_init_from_file(&engine, filepath.c_str(), 0, NULL, NULL, &newSound);
			if (result != MA_SUCCESS) {
				printf("Failed to play sound: %s\n", filepath.c_str());
			}
			sounds[filepath] = newSound;
		}
		ma_sound_start(&sounds[filepath]);
		
	}
	
	void Audio::Stop(std::string filepath) {
		if (!isInitialized) return;

		auto it = sounds.find(filepath);
		if (it != sounds.end()) {
			ma_sound_stop(&it->second);
		}
		else {
			printf("Sound not playing or not found: %s\n", filepath.c_str());
		}
	}


}