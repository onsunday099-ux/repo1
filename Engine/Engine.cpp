#include "engine.h"


namespace engine 
{

    Engine::Engine() = default;

    Engine::~Engine()
    {
        Shutdown();
    }


    bool Engine::Init() 
    {
        if (!m_window.Init() ) {
            spdlog::error("Cant init window: %s", SDL_GetError());
            return false;
        }

        // เรียก Init ของ Renderer โดยส่งพอยน์เตอร์จาก GetWindow() เข้าไป
        if (!m_renderer.Init(m_window.GetWindow())) {
            spdlog::error("Cant init engine %s", SDL_GetError());
            return false;
        }

        m_renderer.LoadTexture("Test/bg/bg2.jpg");
        
        m_running = true;
        //true คือrunอยู่ false คือไม่ได้run
        

        return true;
    }

    void Engine::Shutdown()
    {
        m_renderer.Shutdown();
        m_window.Shutdown();
        SDL_Quit();
    }

    void Engine::ProcessEvents() 
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_EVENT_QUIT)
            {
                m_running = false;

            }

        }
    }


    // เรียก Render ของ Renderer ที่นี่
    void Engine::Update() 
    {
        
    }

    void Engine::Render() 
    {
        m_renderer.Render();
    }

   
    void Engine::Run() 
    {
        

        while (m_running)
        {
            ProcessEvents();
            Update();
            Render();
        }

    }
  
}











