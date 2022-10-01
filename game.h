#ifndef _BOARD_H_
#define _BOARD_H_

#include <ncurses.h> 

class Snake;
class Fruit;

class Game
{
    public:
    Game(){ this->initialize(); }
    void gameStart();
    ~Game();
    private:
    int boardWidth, boardLength, score;
    Snake *snake;
    Fruit *fruit;
    WINDOW *board;
    
    bool is_board_size_change()const;
    void boardResize();
    void initialize();
    void drawBoard();
    void draw(int y, int x, chtype ch);
    void drawFruit(Fruit *fruit);
    void drawSnake(Snake *snake);
    chtype getInput();
    void getEmptySpot(int *y, int *x);
    void gameOver();
};
#endif