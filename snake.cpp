#include "snake.h"
#include "fruit.h"

// get keyboard input 
// change snake direction
int Snake::changeDirection()
{
    //wgetch implicitly refresh the gameWindow
    int choice = wgetch(gameWindow);
    auto it = body.begin();
    std::advance(it, 2);
    bool snakeOnlyHasHead = (it == body.end());

    switch(choice)
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
    return choice;
}

void Snake::updateSnakePos()
{
    auto last_body_block = this->body.end();
    last_body_block = std::prev(last_body_block, 2);
    SnakeBody head_new = this->body.front();
    head_new.bodySymbol = '*';

    this->gameWindowSizeUpdate();
    switch(this->currentDirection)
    {
        case SNAKE_UP:
            head_new.y--;
            if (head_new.y <= 0)
                head_new.y = gameWindowLength - 2;
            break;
        case SNAKE_DOWN:
            head_new.y++;
            if (head_new.y >= gameWindowLength - 1)
                head_new.y = 1;
            break;
        case SNAKE_LEFT:
            head_new.x--;
            if (head_new.x <= 0)
                head_new.x = gameWindowWidth - 2;
            break;
        case SNAKE_RIGHT:
            head_new.x++;
            if (head_new.x >= gameWindowWidth - 1)
                head_new.x = 1;
            break;
        default:
            break;
    }
    if (this->body.begin()->bodySymbol == '*')
        this->body.begin()->bodySymbol = 'o';
    this->body.push_front(head_new);
    if (last_body_block->bodySymbol == '*' || 
        last_body_block->bodySymbol == 'o')
    {
        // pop out old eraser and set new eraser
        this->body.pop_back();
        auto new_eraser = (--this->body.end());
        new_eraser->bodySymbol = ' ';
    }else
        // use old eraser and change last block of snake to '*'
        // representign snake grow through digestion
        last_body_block->bodySymbol = 'o';
}

void Snake::draw() const
{
    //draw snakebody
    for (auto it = body.begin(); it != body.end(); it++)
        mvwaddch(gameWindow, it->y, it->x, it->bodySymbol);
    wrefresh(gameWindow);
}

bool Snake::is_death()const
{
    auto head = this->body.begin();
    
    //check if snake collide with its own body
    for (auto it = ++this->body.begin() ; it != this->body.end(); it++)
        if (head->x == it->x && head->y == it->y)
            return true;
    return false;
}

void Snake::digest()
{
    this->body.begin()->bodySymbol = '#';
}
bool Snake::eatFruit(Fruit *fruit)
{
    auto head = this->body.begin();
    
    return (head->x == fruit->getX() && head->y == fruit->getY());
}

void Snake::gameWindowSizeUpdate()
{
    getmaxyx(this->gameWindow, this->gameWindowLength, this->gameWindowWidth);
}
