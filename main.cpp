#include "snake.h"
#include "fruit.h"
 
void game_over(WINDOW *win, int score)
{

}

bool is_window_size_change(int y, int x)
{
    int yMax, xMax;
    
    getmaxyx(stdscr, yMax, xMax);
    return (y != yMax || x != xMax);
}

void window_resize(WINDOW *win, int *y = NULL, int *x = NULL)
{
    int yMax, xMax;
    
    getmaxyx(stdscr, yMax, xMax);
    wresize(win, yMax, xMax);
    werase(win);
    box(win, 0, 0);
    wrefresh(win);
    if (y && x)
    {
        *y = yMax;
        *x = xMax;
    }
}

int main()
{
    int yMax, xMax;
    WINDOW *gameWindow;
    
    //NCURSES START
    initscr();
    cbreak();
    noecho();
    
    //get window size

    getmaxyx(stdscr, yMax, xMax);
    
    //create game window and configuration

    gameWindow = newwin(yMax,xMax,0,0);
    keypad(gameWindow, true); // eable keypad
    halfdelay(1); //input mode delay
    curs_set(0); // hide curses 
    

    // --

    // driver

    Snake *snake = new Snake(yMax / 2, xMax / 2, gameWindow);
    Fruit *fruit = new Fruit(gameWindow, snake);

    //initial window frame
    window_resize(gameWindow, &yMax, &xMax);
    
    //initial fruit
    fruit->draw();
    while (1)
    {   
        if (snake->is_death())
            break;
        if (snake->changeDirection() == 'x')
            break;
        if (is_window_size_change(yMax, xMax))
        {
            window_resize(gameWindow, &yMax, &xMax);
            //window resize erase fruit, so draw a new fruit
            fruit->kill();
            fruit->draw();
        }
        snake->updateSnakePos();
        snake->draw();
        if (snake->eatFruit(fruit))
        {
            // fruit count minus 1, respawn a new fruit
            fruit->kill();
            fruit->draw();
            //snake eat a fruit
            snake->digest();
        }
    }

    // --
    // NCURSES END
    endwin();
    return 0;
}