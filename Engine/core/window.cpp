#include <SDL3/SDL.h>
#include "window.h"
#include "logger.h"
#include <spdlog/spdlog.h>

namespace window {
	
	Window::Window() = default;
	Window::~Window() {
		Shutdown();
	}
	

	bool Window::Init() {
		

		if (!SDL_Init(SDL_INIT_VIDEO)) {
			
			spdlog::error("SDL_Init failed: %s", SDL_GetError());
			SDL_Log("SDL_Init failed: %s", SDL_GetError());
			return false;
		}

		m_window = SDL_CreateWindow(
			"Window",
			1280,
			720,
			0
		);

		if (!m_window) {
			spdlog::error("Error create window: %s", SDL_GetError());
			return false;
		}

		spdlog::info("Window created successfully");
		return true;
	}

	//void run() {
	//	
	//}

	void Window::Shutdown() {
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}



}
	