#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

namespace window
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Texture* bg_texture = nullptr;
    SDL_Texture* char_texture = nullptr;

    // Viewport configuration
    SDL_Texture* viewport_texture = nullptr;
    int vp_width = 1280;
    int vp_height = 720;

    float char_w = 400.0f;
    float char_h = 400.0f;
    float char_x = 440.0f;
    float char_y = 160.0f;

    char char_file_path[256] = "test/char.png"; // Set default or populate via file dialog
    bool is_running = true;

    void update_viewport_resolution(int new_w, int new_h)
    {
        if (new_w <= 0 || new_h <= 0) return;
        if (new_w == vp_width && new_h == vp_height && viewport_texture != nullptr) return;

        vp_width = new_w;
        vp_height = new_h;

        if (viewport_texture)
        {
            SDL_DestroyTexture(viewport_texture);
            viewport_texture = nullptr;
        }

        viewport_texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            vp_width,
            vp_height
        );
    }

    void load_character_texture(const char* filepath)
    {
        if (!filepath || strlen(filepath) == 0) return;

        SDL_Surface* surface = IMG_Load(filepath);
        if (!surface) return;

        if (char_texture) SDL_DestroyTexture(char_texture);
        char_texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
    }

    void init()
    {
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow("Game Engine Editor", 1600, 900, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, nullptr);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Docking is supported by SDL_Renderer
        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer3_Init(renderer);

        update_viewport_resolution(1280, 720);

        SDL_Surface* bg_surface = IMG_Load("test/bg1.jpg");
        if (bg_surface)
        {
            bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
            SDL_DestroySurface(bg_surface);
        }

        load_character_texture(char_file_path);
    }

    void top_menu()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N")) {}
                if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void render_game_scene()
    {
        if (!viewport_texture) return;

        // 1. Render to Viewport Texture target
        SDL_SetRenderTarget(renderer, viewport_texture);

        SDL_SetRenderDrawColor(renderer, 20, 20, 25, 255);
        SDL_RenderClear(renderer);

        if (bg_texture)
        {
            SDL_RenderTexture(renderer, bg_texture, nullptr, nullptr);
        }

        if (char_texture)
        {
            SDL_FRect dst_rect = { char_x, char_y, char_w, char_h };
            SDL_RenderTexture(renderer, char_texture, nullptr, &dst_rect);
        }

        // 2. Restore Render Target back to main swapchain
        SDL_SetRenderTarget(renderer, nullptr);
    }

    void run()
    {
        while (is_running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL3_ProcessEvent(&event);
                if (event.type == SDL_EVENT_QUIT) is_running = false;
            }

            // Start ImGui frame before invoking any ImGui draw commands
            ImGui_ImplSDLRenderer3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();

            // DockSpace layout container
            ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

            top_menu();

            // Viewport Panel
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("Viewport");

            ImVec2 avail_size = ImGui::GetContentRegionAvail();
            if (avail_size.x > 0.0f && avail_size.y > 0.0f)
            {
                update_viewport_resolution(static_cast<int>(avail_size.x), static_cast<int>(avail_size.y));
            }

            // Render scene to texture now that dimensions are validated
            render_game_scene();

            if (viewport_texture)
            {
                ImGui::Image(
                    reinterpret_cast<ImTextureID>(viewport_texture),
                    ImVec2(static_cast<float>(vp_width), static_cast<float>(vp_height))
                );
            }

            ImGui::End();
            ImGui::PopStyleVar();

            // Inspector Panel
            ImGui::Begin("Inspector");
            ImGui::Text("Viewport Size: %d x %d", vp_width, vp_height);
            ImGui::Separator();
            ImGui::SliderFloat("Pos X", &char_x, 0.0f, static_cast<float>(vp_width));
            ImGui::SliderFloat("Pos Y", &char_y, 0.0f, static_cast<float>(vp_height));
            ImGui::SliderFloat("Width", &char_w, 10.0f, static_cast<float>(vp_width));
            ImGui::SliderFloat("Height", &char_h, 10.0f, static_cast<float>(vp_height));
            ImGui::End();

            // Final screen presentation
            ImGui::Render();

            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
            SDL_RenderClear(renderer);

            ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

            SDL_RenderPresent(renderer);
        }
    }

    void destroy()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        if (viewport_texture) SDL_DestroyTexture(viewport_texture);
        if (char_texture) SDL_DestroyTexture(char_texture);
        if (bg_texture) SDL_DestroyTexture(bg_texture);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);

        SDL_Quit();
    }
}

int main(int argc, char* argv[])
{
    window::init();
    window::run();
    window::destroy();
    return 0;
}