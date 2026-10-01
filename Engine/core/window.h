#pragma once
#include <SDL3/SDL.h>


namespace window {
	
	class Window {
	public:
		Window();
		~Window();

		bool Init();
		//void run();
		void Shutdown();

		SDL_Window* GetWindow() const 
		{ 
			return m_window; 
		}

	private:
		SDL_Window* m_window = nullptr;
		
	
	};


}