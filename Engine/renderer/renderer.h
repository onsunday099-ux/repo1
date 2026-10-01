#pragma once
#include <SDL3/SDL.h>
#include <logger.h>


namespace renderer {

	class Renderer {
	public:
		Renderer();
		~Renderer();

		bool Init(SDL_Window* window);
		bool LoadTexture(const char* filePath);
		void Render();
		void Shutdown();
	private:
		SDL_Renderer* m_renderer = nullptr;
		SDL_Texture* m_texture = nullptr;


	};
}