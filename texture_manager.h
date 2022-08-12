#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Texture_Manager {
public:
    static SDL_Texture* gen_texture(TTF_Font* font, const std::string& text, SDL_Color text_color , SDL_Renderer* renderer);
    static void draw_tex(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect dst);
};