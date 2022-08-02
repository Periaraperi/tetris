#include "tetris.h"

Tetris::Tetris(int screen_width, int screen_height)
:m_width(screen_width), m_height(screen_height), m_grid(std::vector<std::vector<int>>(20,std::vector<int>(10,0)))
{
    if(init_subsystems()) {
        m_running = true;
        srand(time(NULL));
        reset();

        init_static_ui_elements();
        init_dynamic_ui_elements();
    } else {
        m_running = false;
    }
}

Tetris::~Tetris()
{
    SDL_DestroyTexture(m_title);
    SDL_DestroyTexture(m_change_level);
    SDL_DestroyTexture(m_play);
    SDL_DestroyTexture(m_movement);
    SDL_DestroyTexture(m_level_menu);
    SDL_DestroyTexture(m_level_playing);
    SDL_DestroyTexture(m_score_playing);
    SDL_DestroyTexture(m_lines_playing);
    SDL_DestroyTexture(m_next);

    SDL_DestroyTexture(m_game_over);
    SDL_DestroyTexture(m_reset);

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_Quit();
}

bool Tetris::init_subsystems()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) {
        std::cout << "SDL init error: " << SDL_GetError() << '\n';
        return false;
    }

    m_window = SDL_CreateWindow("tetris",SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED,
                                         m_width,m_height,
                                         SDL_WINDOW_SHOWN);
    if(m_window==nullptr) {
        std::cout << "SDL window error: " << SDL_GetError() << '\n';
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
    if(m_renderer==nullptr) {
        std::cout << "SDL Renderer error: " << SDL_GetError() << '\n';
        return false;
    }

    if(TTF_Init()<0) {
        std::cout << "TTF init error: " << TTF_GetError() << '\n';
        return false;
    }
    
    return true;
}

void Tetris::init_static_ui_elements()
{
    m_font = TTF_OpenFont("../assets/fonts/roboto/Roboto-Regular.ttf",30);
    if(m_font==nullptr) {
        std::cout << "Could not open font: " << TTF_GetError() << '\n';
    }

    m_title = Texture_Manager::gen_texture(m_font,"TETRIS",{255,255,255,255},m_renderer);
    m_change_level = Texture_Manager::gen_texture(m_font,"w/s - change level",{255,255,255,255},m_renderer);
    m_play = Texture_Manager::gen_texture(m_font,"space - play",{255,255,255,255},m_renderer);
    m_movement = Texture_Manager::gen_texture(m_font,"wasd - movement",{255,255,255,255},m_renderer);
    m_next = Texture_Manager::gen_texture(m_font,"Next",{255,255,255,255},m_renderer);

    m_game_over = Texture_Manager::gen_texture(m_font,"GAME OVER",{255,255,255,255},m_renderer);
    m_reset = Texture_Manager::gen_texture(m_font,"space - reset",{255,255,255,255},m_renderer);

    m_title_dst = {32*3+10,32,0,0};
    SDL_QueryTexture(m_title,nullptr,nullptr,&m_title_dst.w,&m_title_dst.h);

    m_change_level_dst = {32*2-20,32*2,0,0};
    SDL_QueryTexture(m_change_level,nullptr,nullptr,&m_change_level_dst.w,&m_change_level_dst.h);

    m_play_dst = {32*2-20,32*3,0,0};
    SDL_QueryTexture(m_play,nullptr,nullptr,&m_play_dst.w,&m_play_dst.h);

    m_movement_dst = {32*2-20,32*4,0,0};
    SDL_QueryTexture(m_movement,nullptr,nullptr,&m_movement_dst.w,&m_movement_dst.h);

    m_next_dst = {0,32*24,0,0};
    SDL_QueryTexture(m_next,nullptr,nullptr,&m_next_dst.w,&m_next_dst.h);

    m_game_over_dst = {32*2,32*5,0,0};
    SDL_QueryTexture(m_game_over,nullptr,nullptr,&m_game_over_dst.w,&m_game_over_dst.h);
    m_reset_dst = {32*2,32*6,0,0};
    SDL_QueryTexture(m_reset,nullptr,nullptr,&m_reset_dst.w,&m_reset_dst.h);

}

void Tetris::init_dynamic_ui_elements()
{
    m_level_menu = Texture_Manager::gen_texture(m_font,"Level 0",{255,255,255,255},m_renderer);
    m_level_menu_dst = {32*2-20,32*5,0,0};
    SDL_QueryTexture(m_level_menu,nullptr,nullptr,&m_level_menu_dst.w,&m_level_menu_dst.h);

    m_level_playing = Texture_Manager::gen_texture(m_font,"Level 0",{255,255,255,255},m_renderer);
    m_level_playing_dst = {0,32*20,0,0};
    SDL_QueryTexture(m_level_playing,nullptr,nullptr,&m_level_playing_dst.w,&m_level_playing_dst.h);

    m_score_playing = Texture_Manager::gen_texture(m_font,"Score 0",{255,255,255,255},m_renderer);
    m_score_playing_dst = {0,32*21,0,0};
    SDL_QueryTexture(m_score_playing,nullptr,nullptr,&m_score_playing_dst.w,&m_score_playing_dst.h);

    m_lines_playing = Texture_Manager::gen_texture(m_font,"Lines 0",{255,255,255,255},m_renderer);
    m_lines_playing_dst = {0,32*22,0,0};
    SDL_QueryTexture(m_lines_playing,nullptr,nullptr,&m_lines_playing_dst.w,&m_lines_playing_dst.h);

}

void Tetris::update_texture(SDL_Texture*& tex, SDL_Rect& dst, const std::string& text)
{
    SDL_DestroyTexture(tex);
    tex = Texture_Manager::gen_texture(m_font,text,{255,255,255,255},m_renderer);
    SDL_QueryTexture(tex,nullptr,nullptr,&dst.w,&dst.h);
}

void Tetris::reset_dynamic_ui_elements()
{
    update_texture(m_level_menu,m_level_menu_dst,"Level 0");
    update_texture(m_level_playing,m_level_playing_dst,"Level 0");
    update_texture(m_score_playing,m_score_playing_dst,"Score 0");
    update_texture(m_lines_playing,m_lines_playing_dst,"Lines 0");
}

void Tetris::reset()
{
    m_current_piece = Tetromino(Tetromino_Type(rand()%7));
    m_current_piece.offset(4,-3);
    m_next_piece = Tetromino(Tetromino_Type(rand()%7));
    m_next_piece.offset(1,24);
    m_level = Level::LEVEL_0;
    m_level_score = 0;
    m_total_score = 0;
    m_lines_cleared = 0;
    m_game_state = Game_State::MENU;

    for(auto& y:m_grid)
        for(auto& x:y)
            x = 0;
}

void Tetris::run()
{
    
    unsigned int prev_tick = 0;
    float dt = 0.0f;
    float accumulator = 0.0f;

    while(m_running) {
        unsigned int current_tick = SDL_GetTicks(); // in milliseconds
        unsigned int delta_ticks = current_tick - prev_tick; // in milliseconds
        prev_tick = current_tick; // in milliseconds
        dt = delta_ticks*0.001f; // convert to seconds
        accumulator += dt;
        handle_events();
        while(accumulator>=game_speed[int(m_level)]) {
            update();
            accumulator -= game_speed[int(m_level)];
        }
        render();

        SDL_Delay(1);
    }
}

void Tetris::handle_events()
{
    while(SDL_PollEvent(&m_ev)) {
        if(m_ev.type==SDL_QUIT) {
            m_running = false;
            break;
        } else if(m_ev.type==SDL_KEYDOWN) {
            if(m_game_state==Game_State::PLAYING) {
                if(m_ev.key.keysym.sym==SDLK_a)
                    m_current_piece.move(Vector3<int>(-1,0,0),m_grid);
                if(m_ev.key.keysym.sym==SDLK_s)
                    m_current_piece.move(Vector3<int>(0,1,0),m_grid);
                if(m_ev.key.keysym.sym==SDLK_d)
                    m_current_piece.move(Vector3<int>(1,0,0),m_grid);
            }
        }
        else if(m_ev.type==SDL_KEYUP) {
            if(m_game_state==Game_State::PLAYING) {
                if(m_ev.key.keysym.sym==SDLK_w)
                    m_current_piece.rotate(m_grid);
            } else if(m_game_state==Game_State::MENU) {
                if(m_ev.key.keysym.sym==SDLK_SPACE) {
                    m_game_state = Game_State::PLAYING;
                    break;
                }
                if(m_ev.key.keysym.sym==SDLK_s) {
                    m_level = Level(std::max(int(m_level)-1,0));
                    update_texture(m_level_menu,m_level_menu_dst,"Level "+std::to_string(int(m_level)));
                    update_texture(m_level_playing,m_level_playing_dst,"Level "+std::to_string(int(m_level)));
                }
                if(m_ev.key.keysym.sym==SDLK_w) {
                    m_level = Level(std::min(int(m_level)+1,9));
                    update_texture(m_level_menu,m_level_menu_dst,"Level "+std::to_string(int(m_level)));
                    update_texture(m_level_playing,m_level_playing_dst,"Level "+std::to_string(int(m_level)));
                }
            } else if(m_game_state==Game_State::GAME_OVER) {
                if(m_ev.key.keysym.sym==SDLK_SPACE) {
                    m_game_state = Game_State::MENU;
                    reset_dynamic_ui_elements();
                    reset();
                    break;
                }
            }
        }
        
    }
}

void Tetris::update()
{
    if(!(m_game_state==Game_State::PLAYING))
        return;
    if(!m_current_piece.go_down(m_grid)) {
        if(game_over()) {
            m_game_state = Game_State::GAME_OVER;
            return;
        }
        fix_current_piece();
        int lines = clear_lines();
        if(lines>0) {
            m_lines_cleared += lines;
            update_texture(m_lines_playing,m_lines_playing_dst,"Lines "+std::to_string(m_lines_cleared));
            m_level_score += (int(m_level)+1)*score_per_line[lines-1];
            m_total_score += (int(m_level)+1)*score_per_line[lines-1];
            update_texture(m_score_playing,m_score_playing_dst,"Score "+std::to_string(m_total_score));
            if(m_level_score>=need_to_levelup*int(m_level)) {
                m_level = Level(std::min((int(m_level)+1),int(Level::LEVEL_9)));
                update_texture(m_level_playing,m_level_playing_dst,"Level "+std::to_string(int(m_level)));
                m_level_score = 0;
            }
        }
        
        m_current_piece = Tetromino(m_next_piece.get_type());
        m_current_piece.offset(4,-3);
        m_next_piece = Tetromino(Tetromino_Type(rand()%7));
        m_next_piece.offset(1,24);
    }
}

void Tetris::render()
{
    SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
    SDL_RenderClear(m_renderer);

    SDL_Rect bottom = {0,32*20,10*32,6*32};
    SDL_SetRenderDrawColor(m_renderer,64,63,61,255);
    SDL_RenderFillRect(m_renderer,&bottom);

    if(m_game_state==Game_State::MENU) {
        Texture_Manager::draw_tex(m_renderer,m_title,m_title_dst);
        Texture_Manager::draw_tex(m_renderer,m_change_level,m_change_level_dst);
        Texture_Manager::draw_tex(m_renderer,m_play,m_play_dst);
        Texture_Manager::draw_tex(m_renderer,m_movement,m_movement_dst);
        Texture_Manager::draw_tex(m_renderer,m_level_menu,m_level_menu_dst);
    } else {
        auto positions = m_current_piece.get_positions();
        for(int i=0; i<positions.size(); ++i) {
            SDL_Rect rect = {positions[i].x*32,positions[i].y*32,32,32};
            Vector3<int> c = colors[m_current_piece.get_color_id()];
            SDL_SetRenderDrawColor(m_renderer,c.x,c.y,c.z,255);
            SDL_RenderFillRect(m_renderer,&rect);
        }
        auto positions_next = m_next_piece.get_positions();
        for(int i=0; i<positions_next.size(); ++i) {
            SDL_Rect rect = {positions_next[i].x*32,positions_next[i].y*32,32,32};
            Vector3<int> c = colors[m_next_piece.get_color_id()];
            SDL_SetRenderDrawColor(m_renderer,c.x,c.y,c.z,255);
            SDL_RenderFillRect(m_renderer,&rect);
        }

        for(int y=0; y<m_grid.size(); ++y) {
            for(int x=0; x<m_grid[y].size(); ++x) {
                    if(m_grid[y][x]!=0) {
                    SDL_Rect rect = {x*32,y*32,32,32};
                    Vector3<int> c = colors[m_grid[y][x]-1];
                    SDL_SetRenderDrawColor(m_renderer,c.x,c.y,c.z,255);
                    SDL_RenderFillRect(m_renderer,&rect);
                }
            }
        }

        Texture_Manager::draw_tex(m_renderer,m_level_playing,m_level_playing_dst);
        Texture_Manager::draw_tex(m_renderer,m_score_playing,m_score_playing_dst);
        Texture_Manager::draw_tex(m_renderer,m_lines_playing,m_lines_playing_dst);

        if(m_game_state==Game_State::GAME_OVER) {
            Texture_Manager::draw_tex(m_renderer,m_game_over,m_game_over_dst);
            Texture_Manager::draw_tex(m_renderer,m_reset,m_reset_dst);
        }

    }

    SDL_RenderPresent(m_renderer);
}

void Tetris::fix_current_piece()
{
    auto positions = m_current_piece.get_positions();
    for(auto& p:positions) {
        m_grid[p.y][p.x] = m_current_piece.get_color_id()+1;
    }
}

int Tetris::clear_lines()
{
    std::vector<int> lines; // store line's row index

    // detect lines
    for(int y=0; y<m_grid.size(); ++y) {
        bool is_line = true;
        for(int x=0; x<m_grid[y].size(); ++x) {
            if(m_grid[y][x]==0) {
                is_line = false;
                break;
            }
        }
        if(is_line) {
            lines.push_back(y);
        }
    }

    // clear
    for(int i=0; i<lines.size(); ++i) {
        for(int y=lines[i]; y>0; --y) {
            for(int x=0; x<10; ++x) m_grid[y][x] = m_grid[y-1][x];
            for(int x=0; x<10; ++x) m_grid[y-1][x] = 0;
        }
    }
    return lines.size();
}

bool Tetris::game_over()
{
    auto positions = m_current_piece.get_positions();
    for(auto& p:positions) {
        if(p.y<0) return true;
    }
    return false;
}