#include "renderer.h"
#include <spdlog/spdlog.h>

namespace Renderer
{
    static SDL_Renderer* renderer = nullptr;

    bool Init(SDL_Window* window)
    {
        renderer = SDL_CreateRenderer(window, NULL);
        if (!renderer)
        {
            spdlog::error("SDL_CreateRenderer failed: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    void Clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    }

    void DrawTexture(SDL_Texture* texture, const SDL_FRect* src, const SDL_FRect* dst)
    {
        if (texture)
        {
            SDL_RenderTexture(renderer, texture, src, dst);
        }
    }

    void Present()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Renderer* GetNativeRenderer()
    {
        return renderer;
    }

    void Destroy()
    {
        if (renderer)
        {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
    }
}