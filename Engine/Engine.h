#pragma once
#include "window.h"
#include "renderer/renderer.h"
#include "script/script_parser.h"
#include <spdlog/spdlog.h>

namespace engine {

	class Engine {
	public:
		Engine();
		~Engine();

		bool Init();
		void Run();
		void Shutdown();

	private:
		void ProcessEvents();
		void Update();
		void Render();

	private:
		bool m_running = false;

		window::Window m_window;
		renderer::Renderer m_renderer;
		//renderer::Renderer m_renderer;
		//audio::Audio m_audio;
	};
	
}