#include "engine.h"
#include "window.h"
#include "timer.h"
#include "gui_layer.h"
#include "scene_manager.h"
#include "game_scene.h"
#include "event_manager.h"
#include "audio.h"
#include "renderer.h"
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include <memory>

namespace Engine
{
    static bool is_running = true;

    static void Mainloop()
    {
        while (is_running)
        {
            Timer::FrameStart();

            if (!EventManager::PollEvents())
            {
                is_running = false;
            }

            SceneManager::Update(Timer::GetDeltaTime());

            SceneManager::Render();

            GuiLayer::BeginFrame();
            GuiLayer::DrawAudioPanel();
            GuiLayer::EndFrame(Renderer::GetNativeRenderer());

            Renderer::Present();

            Timer::FrameEnd();
        }
    }

    bool Init()
    {
        Timer::Init(240);

        if (!Window::Init("SDL3 From Engine", 1280, 720))
        {
            return false;
        }

        if (!Renderer::Init(Window::GetNativeWindow()))
        {
            spdlog::error("Renderer Init failed");
            return false;
        }

        if (!audio::Init())
        {
            spdlog::error("AudioInit failed");
            return false;
        }

        if (!GuiLayer::Init(Window::GetNativeWindow(), Renderer::GetNativeRenderer()))
        {
            spdlog::error("GuiLayer Init failed");
            return false;
        }

        SceneManager::ChangeScene(std::make_unique<GameScene>());

        spdlog::info("Engine initialized");
        return true;
    }

    void Run()
    {
        Mainloop();
    }

    void Destroy()
    {
        SceneManager::Destroy();
        GuiLayer::Destroy();
        audio::DestroyAudio();
        Renderer::Destroy();
        Window::Destroy();
    }
}