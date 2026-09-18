#include "timer.h"

namespace Timer
{
    static Uint64 frame_start_time = 0;
    static Uint64 last_frame_time = 0;
    static float delta_time = 0.0f;

    static float current_fps = 0.0f;
    static int frame_count = 0;
    static Uint64 fps_start_time = 0;

    static int target_fps = 240;

    void Init(int target)
    {
        target_fps = target;
        frame_start_time = SDL_GetTicks();
        last_frame_time = frame_start_time;
        fps_start_time = frame_start_time;
    }

    void FrameStart()
    {
        frame_start_time = SDL_GetTicks();
        delta_time = (frame_start_time - last_frame_time) / 1000.0f;
        last_frame_time = frame_start_time;

        frame_count++;
        if (frame_start_time - fps_start_time >= 1000)
        {
            current_fps = frame_count / ((frame_start_time - fps_start_time) / 1000.0f);
            frame_count = 0;
            fps_start_time = frame_start_time;
        }
    }

    void FrameEnd()
    {
        if (target_fps <= 0) return;

        Uint64 target_frame_time = 1000 / target_fps;
        Uint64 frame_time = SDL_GetTicks() - frame_start_time;

        if (frame_time < target_frame_time)
        {
            SDL_Delay(target_frame_time - frame_time);
        }
    }

    float GetFPS()
    {
        return current_fps;
    }

    float GetDeltaTime()
    {
        return delta_time;
    }

    void SetTargetFPS(int target)
    {
        target_fps = target;
    }
}