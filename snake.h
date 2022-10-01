#ifndef _SNAKE_H_
#define _SNAKE_H_

#include "obj.h"
#include <list>

class Fruit;

class SnakeBody : public Obj
{
    public:
    SnakeBody(int _y = 0, int _x = 0, char _bodyShape = 'o') : Obj(_y, _x)  
    { 
        bodyShape = _bodyShape; 
    }
    char getBodyShape()const{ return bodyShape; }
    void setBodyShape(char ch) { bodyShape = ch; }
    private:
    char bodyShape;
};

class Snake
{
    public:
    
    Snake(int _y = 0, int _x = 0, int _length = 0, int _width = 0)
    : boardLength(_length), boardWidth(_width)
    {
        SnakeBody head(_y, _x, '*');
        SnakeBody eraser(_y, _x - 1, ' ');

        body.push_back(head);
        body.push_back(eraser);
        currentDirection = SNAKE_RIGHT;
    }
    bool snakeFindFruit(Fruit *fruit)const;
    bool is_death()const;
    void digest();
    void updateBoardSize(int _length, int _width);
    void updateSnakePos();
    void changeDirection(int keyInput);
    const std::list<SnakeBody> getSnakeBody(){ return body; };
    private:
        enum direction{ SNAKE_UP = KEY_UP , SNAKE_DOWN = KEY_DOWN, 
        SNAKE_LEFT = KEY_LEFT, SNAKE_RIGHT = KEY_RIGHT };
    int currentDirection, boardWidth, boardLength;
    std::list<SnakeBody> body;                    
};

#endif