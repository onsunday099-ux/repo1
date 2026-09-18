#pragma once
#include <SDL3/SDL.h>

namespace GuiLayer
{
    bool Init(SDL_Window* window, SDL_Renderer* renderer);
    void ProcessEvent(const SDL_Event& event);
    void BeginFrame();
    void DrawAudioPanel();
    void EndFrame(SDL_Renderer* renderer);
    void Destroy();
}