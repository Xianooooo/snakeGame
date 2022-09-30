#ifndef _FRUIT_H
#define _FRUIT_H

#include <random>
#include <ncurses.h>

class Snake;

class Fruit
{
    public:
    Fruit(WINDOW *gameWindow = NULL, const Snake *const snake = NULL)
    {
        this->gameWindow = gameWindow;
        this->gameWindowSizeUpdate();
        this->snake = snake;
        this->getPos();
        count = 0;
    }
    void draw();
    int getY()const{ return y; }
    int getX()const{ return x; }
    int getCount()const{ return count; }
    void kill(){ count--; }
    
    private:
    WINDOW *gameWindow;
    const Snake *snake;
    int gameWindowWidth, gameWindowLength, x, y, count;
    
    void gameWindowSizeUpdate();
    void getPos();
};


#endif