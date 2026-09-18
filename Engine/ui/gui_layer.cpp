#include "gui_layer.h"
#include "audio.h"
#include "timer.h"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

namespace GuiLayer
{
    static float bgm_volume = 1.0f;
    static float voice_volume = 1.0f;
    static float sfx_volume = 1.0f;
    static char text_buffer[128] = "";

    bool Init(SDL_Window* window, SDL_Renderer* renderer)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        if (!ImGui_ImplSDL3_InitForSDLRenderer(window, renderer))
        {
            return false;
        }

        if (!ImGui_ImplSDLRenderer3_Init(renderer))
        {
            return false;
        }

        return true;
    }

    void ProcessEvent(const SDL_Event& event)
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
    }

    void BeginFrame()
    {
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void DrawAudioPanel()
    {
        ImGui::Begin("Audio Control Panel");
        ImGui::Text("FPS: %.1f", Timer::GetFPS());
        ImGui::Separator();

        ImGui::Text("BGM Control");
        ImGui::InputText("BGM File", text_buffer, IM_ARRAYSIZE(text_buffer));

        if (ImGui::Button("Play BGM (Loop + Fade 2s)"))
        {
            audio::PlayBGM(text_buffer, true, 2.0f);
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop BGM (Fade 2s)"))
        {
            audio::StopBGM(2.0f);
        }

        if (ImGui::SliderFloat("BGM Volume", &bgm_volume, 0.0f, 1.0f, "%.2f"))
        {
            audio::SetVolume(audio::Channel::BGM, bgm_volume);
        }

        ImGui::Separator();

        ImGui::Text("Voice Control");
        if (ImGui::Button("Play Voice Line"))
        {
            audio::PlayVoice("test/voice.wav");
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop Voice"))
        {
            audio::StopVoice();
        }

        if (ImGui::SliderFloat("Voice Volume", &voice_volume, 0.0f, 1.0f, "%.2f"))
        {
            audio::SetVolume(audio::Channel::VOICE, voice_volume);
        }

        ImGui::Separator();

        ImGui::Text("SFX Control");
        if (ImGui::Button("Play Click SFX"))
        {
            audio::PlaySFX("test/click.wav");
        }

        if (ImGui::SliderFloat("SFX Volume", &sfx_volume, 0.0f, 1.0f, "%.2f"))
        {
            audio::SetVolume(audio::Channel::SFX, sfx_volume);
        }

        ImGui::End();
    }

    void EndFrame(SDL_Renderer* renderer)
    {
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
    }

    void Destroy()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
}