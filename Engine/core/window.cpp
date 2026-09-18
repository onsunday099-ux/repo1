#include "window.h"
#include <spdlog/spdlog.h>

namespace Window
{
    static SDL_Window* window = nullptr;

    bool Init(const char* title, int width, int height)
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            spdlog::error("SDL_Init failed: {}", SDL_GetError());
            return false;
        }

        window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
        if (!window)
        {
            spdlog::error("SDL_CreateWindow failed: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    SDL_Window* GetNativeWindow()
    {
        return window;
    }

    Uint32 GetWindowID()
    {
        if (window)
        {
            return SDL_GetWindowID(window);
        }
        return 0;
    }

    void Destroy()
    {
        if (window)
        {
            SDL_DestroyWindow(window);
            window = nullptr;
        }

        SDL_Quit();
    }
}


