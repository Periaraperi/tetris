#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>
#include <time.h>

#include "tetromino.h"
#include "texture_manager.h"

enum class Level {
    LEVEL_0,
    LEVEL_1,
    LEVEL_2,
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    LEVEL_6,
    LEVEL_7,
    LEVEL_8,
    LEVEL_9
};

enum class Game_State {
    MENU,
    PLAYING,
    GAME_OVER
};

const int need_to_levelup = 2000;
static std::vector<float> game_speed = {0.40f,0.35f,0.30f,0.25f,0.20f,0.15f,0.10f,0.08f,0.06f,0.05f};
static std::vector<int> score_per_line = {40, 100, 300, 1200};

class Tetris {
public:
    Tetris(int screen_width, int screen_height);
    ~Tetris();

    void run();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    int m_width;
    int m_height;
    bool m_running;
    TTF_Font* m_font;
    SDL_Event m_ev;

    // ui elements
    
    SDL_Texture* m_title;
    SDL_Rect m_title_dst;
    SDL_Texture* m_change_level;
    SDL_Rect m_change_level_dst;
    SDL_Texture* m_play;
    SDL_Rect m_play_dst;
    SDL_Texture* m_movement;
    SDL_Rect m_movement_dst;
    SDL_Texture* m_next;
    SDL_Rect m_next_dst;

    SDL_Texture* m_level_menu;
    SDL_Rect m_level_menu_dst;
    
    SDL_Texture* m_level_playing;
    SDL_Rect m_level_playing_dst;
    SDL_Texture* m_score_playing;
    SDL_Rect m_score_playing_dst;
    SDL_Texture* m_lines_playing;
    SDL_Rect m_lines_playing_dst;
    

    SDL_Texture* m_game_over;
    SDL_Rect m_game_over_dst;
    SDL_Texture* m_reset;
    SDL_Rect m_reset_dst;
    // 


    std::vector<std::vector<int>> m_grid;
    Tetromino m_current_piece;
    Tetromino m_next_piece;
    Game_State m_game_state;
    Level m_level;
    int m_total_score;
    int m_level_score;
    int m_lines_cleared;

    bool init_subsystems();
    void init_static_ui_elements();
    void init_dynamic_ui_elements();
    void reset_dynamic_ui_elements();
    void update_texture(SDL_Texture*& tex, SDL_Rect& dst, const std::string& text);

    void handle_events();
    void update();
    void render();

    void reset();
    void fix_current_piece();
    int clear_lines();
    bool game_over();

};