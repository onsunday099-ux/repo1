#pragma once
#include <SDL3/SDL.h>

namespace Window
{
    bool Init(const char* title, int width, int height);
    SDL_Window* GetNativeWindow();
    Uint32 GetWindowID();
    void Destroy();
}