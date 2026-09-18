#include "input.h"
#include <imgui.h>
#include <unordered_map>

namespace Input {
    static SDL_FPoint mouse_pos = { 0.0f, 0.0f };
    static std::unordered_map<Uint8, bool> mouse_just_pressed;
    static std::unordered_map<SDL_Keycode, bool> keys_just_pressed;

    void BeginNewFrame() {
        mouse_just_pressed.clear();
        keys_just_pressed.clear();
        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    }

    void ProcessEvent(const SDL_Event& event) {
        ImGuiIO& io = ImGui::GetIO();

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (!io.WantCaptureMouse) {
                mouse_just_pressed[event.button.button] = true;
            }
        }
        else if (event.type == SDL_EVENT_KEY_DOWN) {
            if (!io.WantCaptureKeyboard && !event.key.repeat) {
                keys_just_pressed[event.key.key] = true;
            }
        }
    }

    SDL_FPoint GetMousePosition() {
        return mouse_pos;
    }

    bool IsMouseButtonJustPressed(Uint8 button) {
        auto it = mouse_just_pressed.find(button);
        return it != mouse_just_pressed.end() && it->second;
    }

    bool IsKeyJustPressed(SDL_Keycode key) {
        auto it = keys_just_pressed.find(key);
        return it != keys_just_pressed.end() && it->second;
    }
}