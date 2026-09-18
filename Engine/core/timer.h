#pragma once
#include <SDL3/SDL.h>

namespace Timer
{
    void Init(int target_fps = 240);
    void FrameStart();
    void FrameEnd();
    float GetFPS();
    float GetDeltaTime();
    void SetTargetFPS(int target_fps);
}