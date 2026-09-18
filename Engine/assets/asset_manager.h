#pragma once
#include <SDL3/SDL.h>
#include <string>

namespace Asset_Manager
{
    extern SDL_Texture* bg_texture;
    extern SDL_Texture* char_texture;

    SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filepath);
    bool LoadAssets(SDL_Renderer* renderer);
    void DestroyAssets();
}