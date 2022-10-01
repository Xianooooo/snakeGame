#include "game.h"

//driver
int main()
{
    //NCURSES START
    initscr();

    Game *snake_game = new Game();
    snake_game->gameStart();
    //NCURSES END
    endwin();
    delete snake_game;
    return 0;
}