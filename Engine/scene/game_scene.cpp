#include "game_scene.h"
#include "input.h"
#include "renderer.h"
#include "asset_manager.h"
#include <SDL3/SDL.h>
#include <cstdio>

void GameScene::Init()
{
    Asset_Manager::LoadAssets(Renderer::GetNativeRenderer());
}

void GameScene::Update(float delta_time)
{
    (void)delta_time;

    if (Input::IsMouseButtonJustPressed(SDL_BUTTON_LEFT) || Input::IsKeyJustPressed(SDLK_SPACE))
    {
        std::printf("Advance dialogue!\n");
    }

    if (Input::IsKeyJustPressed(SDLK_LCTRL))
    {
        std::printf("Skip\n");
    }
}

void GameScene::Render()
{
    Renderer::Clear(255, 255, 255, 255);

    Renderer::DrawTexture(Asset_Manager::bg_texture);
    Renderer::DrawTexture(Asset_Manager::char_texture);
}

void GameScene::Destroy()
{
    Asset_Manager::DestroyAssets();
}