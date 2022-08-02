#include "texture_manager.h"

SDL_Texture* Texture_Manager::gen_texture(TTF_Font* font, const std::string& text, SDL_Color text_color, SDL_Renderer* renderer)
{
    SDL_Surface* tmp = TTF_RenderText_Solid(font,text.c_str(),text_color);
    if(tmp==nullptr) {
        std::cout << "Could not render text: " << TTF_GetError() << '\n';
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer,tmp);
    if(tex==nullptr) {
        std::cout << "Could not create text texture: " << SDL_GetError() << '\n';
    }
    SDL_FreeSurface(tmp);
    return tex;
}

void Texture_Manager::draw_tex(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect dst)
{
    SDL_RenderCopy(renderer,texture,nullptr,&dst);
}