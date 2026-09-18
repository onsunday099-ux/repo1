#include "event_manager.h"
#include "gui_layer.h"
#include "input.h"
#include "window.h"
#include <SDL3/SDL.h>

namespace EventManager
{
    bool PollEvents()
    {
        Input::BeginNewFrame();

        bool keep_running = true;
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            GuiLayer::ProcessEvent(event);

            if (event.type == SDL_EVENT_QUIT)
            {
                keep_running = false;
            }

            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == Window::GetWindowID())
            {
                keep_running = false;
            }

            Input::ProcessEvent(event);
        }

        return keep_running;
    }
}