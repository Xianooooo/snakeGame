#include "fruit.h"
#include "snake.h"

void Fruit::getPos()
{   

    std::random_device device;
    std::mt19937 generator(device());
    this->gameWindowSizeUpdate();
    std::uniform_int_distribution<int> dist1(1, this->gameWindowLength - 2);
    std::uniform_int_distribution<int> dist2(1, this->gameWindowWidth - 2);
    bool pass = true;
    auto endd = --this->snake->body.end();
    do
    {
        this->y = dist1(generator);
        this->x = dist2(generator);
        pass = true;
        
        for(auto it = this->snake->body.begin(); it != endd; it++)
            if (it->y == this->y && it->x == this->x)
                pass = false;
    } while(!pass);
}

void Fruit::draw() 
{
    this->getPos();
    mvwaddch(this->gameWindow, this->y, this->x, '@');
    wrefresh(this->gameWindow);
    this->count++;
}

void Fruit::gameWindowSizeUpdate()
{
    getmaxyx(this->gameWindow, this->gameWindowLength, this->gameWindowWidth);
}