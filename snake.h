#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <list>
#include <iterator>
#include <ncurses.h>
#include <unistd.h>

class Fruit;

class Snake{
    private:
    
    class SnakeBody
    {
        public:
        int y, x;
        char bodySymbol;

        SnakeBody(int y = 0, int x = 0, char bodySymbol = '*')
        {
            this->y = y;
            this->x = x;
            this->bodySymbol = bodySymbol;
        }
        SnakeBody(const SnakeBody &t)
        {
            this->y = t.y;
            this->x = t.x;
            this->bodySymbol = t.bodySymbol;
        }
        SnakeBody& operator=(const SnakeBody &t)
        {
            if (this == &t)
                return *this;
            this->y = t.y;
            this->x = t.x;
            this->bodySymbol = t.bodySymbol;
            return *this;
        }
    };
    enum direction{ SNAKE_UP = KEY_UP , SNAKE_DOWN = KEY_DOWN, 
                    SNAKE_LEFT = KEY_LEFT, SNAKE_RIGHT = KEY_RIGHT };
    std::list<SnakeBody> body;
    WINDOW *gameWindow;
    int gameWindowWidth, gameWindowLength, currentDirection, score;

    //helper
    void gameWindowSizeUpdate();
        
    public:
    Snake(int y = 0, int x = 0, WINDOW *gameWindow = NULL)
    {
        SnakeBody head(y, x, '*');
        SnakeBody eraser(y, x - 1, ' ');

        this->body.push_front(head);
        this->body.push_back(eraser);
        this->gameWindow = gameWindow;
        gameWindowSizeUpdate();
        this->currentDirection = SNAKE_RIGHT;
        score = 0;
    }
    int changeDirection();
    void updateSnakePos();
    void draw()const;
    bool is_death()const;
    bool eatFruit(Fruit *fruit);
    void digest();
    int showScore()const{ return score; }
    friend class Fruit;
};
#endif