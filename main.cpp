#include "tetris.h"

int main()
{
    Tetris* game = new Tetris(10*32,26*32);
    game->run();
    delete game;
    return 0;
}
