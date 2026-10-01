#include "renderer.h"
#include <SDL3_image/SDL_image.h>


namespace renderer {

	Renderer::Renderer() = default;

	Renderer::~Renderer() {
		Shutdown();
	}

	bool Renderer::Init(SDL_Window* window) {
		
		if (!window) {
			spdlog::error("Renderer init: {}",SDL_GetError());
			return false;
		}

		m_renderer = SDL_CreateRenderer(window, nullptr);

		if (!m_renderer) {
			spdlog::error("Failed to create renderer: {}", SDL_GetError());
			return false;
		}
		spdlog::info("Renderer created successfully");
		return true;
	}

	bool Renderer::LoadTexture(const char* filePath) {
		if (!m_renderer) {
			spdlog::error("Cannot load texture: Renderer not init");
			return false;
		}

		m_texture = IMG_LoadTexture(m_renderer, filePath);

		if (!m_texture) {
			spdlog::error("Failed to load image {}: {}", filePath, SDL_GetError());
			return false;
		}

		spdlog::info("Loaded image successfully: {}", filePath);
		return true;
	}

	void Renderer::Render()
	{
		if (!m_renderer) return;

		SDL_RenderClear(m_renderer);

		if (m_texture) {
			SDL_RenderTexture(m_renderer, m_texture, nullptr, nullptr);
		}
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::Shutdown()
	{
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
		}

		if (m_renderer) {
			SDL_DestroyRenderer(m_renderer);
			m_renderer = nullptr;
		}
	}
}

//.dds