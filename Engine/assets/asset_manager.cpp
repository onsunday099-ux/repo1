#include "asset_manager.h"
#include <SDL3_image/SDL_image.h>
#include <spdlog/spdlog.h>

namespace Asset_Manager
{
    SDL_Texture* bg_texture = nullptr;
    SDL_Texture* char_texture = nullptr;

    SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filepath)
    {
        SDL_Texture* texture = IMG_LoadTexture(renderer, filepath.c_str());
        if (!texture)
        {
            spdlog::error("Failed to load texture [{}]: {}", filepath, SDL_GetError());
        }
        return texture;
    }

    bool LoadAssets(SDL_Renderer* renderer)
    {
        bg_texture = LoadTexture(renderer, "test/bg1.jpg");
        if (!bg_texture) return false;

        char_texture = LoadTexture(renderer, "test/ch3.png");
        if (!char_texture) return false;

        return true;
    }

    void DestroyAssets()
    {
        if (bg_texture)
        {
            SDL_DestroyTexture(bg_texture);
            bg_texture = nullptr;
        }

        if (char_texture)
        {
            SDL_DestroyTexture(char_texture);
            char_texture = nullptr;
        }
    }
}