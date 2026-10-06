#pragma once
#include <iostream>
#include <miniaudio.h>
#include <unordered_map>

namespace audio {

	class Audio {
	private:
		ma_result result;
		ma_engine engine;
		bool isInitialized = false;

		std::unordered_map<std::string, ma_sound> sounds;

	public:
		Audio();
		~Audio();

		bool Init();
		void Play(std::string filepath);
		void Stop(std::string filepath);

		void Shutdown();
	
	};
}