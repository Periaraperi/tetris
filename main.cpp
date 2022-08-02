#include "tetris.h"

int main()
{
    Tetris* game = new Tetris(10*32,27*32);
    game->run();
    delete game;
    return 0;
}
