#include "snake.h"
#include "fruit.h"

void Snake::updateBoardSize(int _length, int _width)
{
    boardLength = _length;
    boardWidth = _width;
}

void Snake::changeDirection(int keyInput)
{
    auto it = body.begin();
    std::advance(it, 2);
    bool snakeOnlyHasHead = (it == body.end());

    switch(keyInput)
    {
        case KEY_UP:
            if (!(this->currentDirection == SNAKE_DOWN
                    && !snakeOnlyHasHead))
                this->currentDirection = SNAKE_UP;
            break;
        case KEY_LEFT:
            if (!(this->currentDirection == SNAKE_RIGHT
                    && !snakeOnlyHasHead))
                this->currentDirection = SNAKE_LEFT;
            break;
        case KEY_DOWN:
            if (!(this->currentDirection == SNAKE_UP
                    && !snakeOnlyHasHead))
                this->currentDirection = SNAKE_DOWN;
            break;
        case KEY_RIGHT:
            if (!(this->currentDirection == SNAKE_LEFT
                    && !snakeOnlyHasHead))
                this->currentDirection = SNAKE_RIGHT;
            break;
        default:
            break;
    }
}

void Snake::updateSnakePos()
{
    auto last_body_block = this->body.end();
    last_body_block = std::prev(last_body_block, 2);
    SnakeBody head_new = this->body.front();
    head_new.setBodyShape('*');
    
    switch(this->currentDirection)
    {
        case SNAKE_UP:
            head_new.setY(head_new.getY() - 1);
            if (head_new.getY() <= 0)
                head_new.setY(boardLength - 2);
            break;
        case SNAKE_DOWN:
            head_new.setY(head_new.getY() + 1);
            if (head_new.getY() >= boardLength - 1)
                head_new.setY(1);
            break;
        case SNAKE_LEFT:
            head_new.setX(head_new.getX() - 1);
            if (head_new.getX() <= 0)
                head_new.setX(boardWidth - 2);
            break;
        case SNAKE_RIGHT:
            head_new.setX(head_new.getX() + 1);
            if (head_new.getX() >= boardWidth - 1)
                head_new.setX(1);
            break;
        default:
            break;
    }
    if (this->body.begin()->getBodyShape() == '*')
        this->body.begin()->setBodyShape('o');
    this->body.push_front(head_new);
    if (last_body_block->getBodyShape() == '*' || 
        last_body_block->getBodyShape() == 'o')
    {
        // pop out old eraser and set new eraser
        this->body.pop_back();
        auto new_eraser = (--this->body.end());
        new_eraser->setBodyShape(' ');
    }else
        // use old eraser and change last block of snake to '*'
        // representign snake grow through digestion
        last_body_block->setBodyShape('o');
}

// grow body
void Snake::digest()
{
    this->body.begin()->setBodyShape('#');
}

bool Snake::is_death()const
{
    auto head = this->body.begin();
    
    //check if snake collide with its own body
    for (auto it = ++this->body.begin() ; it != this->body.end(); it++)
        if (head->getX() == it->getX() && head->getY() == it->getY())
            return true;
    return false;
}

bool Snake::snakeFindFruit(Fruit *fruit)const
{
    auto head = this->body.begin();

    return (head->getX() == fruit->getX() && head->getY() == fruit->getY());
}