#pragma once
#include <SDL3/SDL.h>

namespace Renderer
{
    bool Init(SDL_Window* window);
    void Clear(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255);
    void DrawTexture(SDL_Texture* texture, const SDL_FRect* src = nullptr, const SDL_FRect* dst = nullptr);
    void Present();
    SDL_Renderer* GetNativeRenderer();
    void Destroy();
}