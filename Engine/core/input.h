#pragma once
#include <SDL3/SDL.h>

namespace Input {
    void BeginNewFrame();
    void ProcessEvent(const SDL_Event& event);

    SDL_FPoint GetMousePosition();
    bool IsMouseButtonJustPressed(Uint8 button);
    bool IsKeyJustPressed(SDL_Keycode key);
}