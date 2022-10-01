#include "game.h"
#include "snake.h"
#include "fruit.h"

void Game::initialize()
{
    //set boardWidth and boardLength to standard screen size
    getmaxyx(stdscr, boardLength, boardWidth);
    this->board = newwin(boardLength, boardWidth, 0, 0);
    score = 0;
    noecho(); // no echo user input
    keypad(board, true);// enable keypad
    halfdelay(1);
    curs_set(0); // hide curses
    
}

//standard screen size change

bool Game::is_board_size_change()const
{
    int y, x;

    getmaxyx(stdscr, y, x);
    return (boardLength != y || boardWidth != x);
}

// erase board when resize
void Game::boardResize()
{
    getmaxyx(stdscr, boardLength, boardWidth);
    wresize(board, boardLength, boardWidth);
    werase(board);
    //update snake fruit
}

void Game::drawBoard()
{
    box(board, 0, 0);
}

void Game::getEmptySpot(int *y, int *x)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> dist1(1,  boardWidth - 2);
    std::uniform_int_distribution<int> dist2(1,  boardLength - 2);
    if (!y || !x)
        return ;
    do
    {
        *y = dist2(generator);
        *x = dist1(generator);
    } while (mvwinch(board, *y, *x) != ' ');
}

chtype Game::getInput()
{ 
    //wtimeout(board, 500);
    return wgetch(board); 
}

void Game::draw(int y, int x, chtype ch){ mvwaddch(board, y, x, ch); }

void Game::drawFruit(Fruit *fruit)
{
    this->draw(fruit->getY(), fruit->getX(), '@');
}

void Game::drawSnake(Snake *snake)
{
    auto snakeBody = snake->getSnakeBody();
    
    for (auto it = snakeBody.begin(); it != snakeBody.end(); it++)
        draw(it->getY(), it->getX(), it->getBodyShape());
}

void Game::gameOver()
{
    int choice = 0;

    werase(board);
    mvwprintw(board, 1, 1,"Good game! Your score: %d", score);
    mvwprintw(board, 3, 1,"Press g to start a new game");
    mvwprintw(board, 4, 1,"Press x to quit the game");
    wrefresh(board);
    while (choice != 'g' && choice != 'x')
        choice = getInput();
    if (choice == 'g')
        gameStart();
}

void Game::gameStart()
{
    Fruit *fruit = new Fruit();
    Snake *snake = new Snake(boardLength / 2, boardWidth / 2,
                            boardLength, boardWidth);
    int input, fruitX, fruitY;
    bool ibsc = false;

    score = 0;
    werase(board);
    drawBoard();
    wrefresh(board); 
    while (1)
    {
        // process input
        input = getInput();
        // update model
        ibsc = is_board_size_change();
        if (ibsc)
        {
            boardResize();
            snake->updateBoardSize(boardLength, boardWidth);
            if (fruit->getCount() > 0)
                fruit->setCount(0);
        }
        if (!fruit->getCount())
        {
            fruit->Add();
            getEmptySpot(&fruitY, &fruitX);
            fruit->UpdateFruitPos(fruitY, fruitX);
        }
        snake->changeDirection(input);
        if (fruit->getCount() && snake->snakeFindFruit(fruit))
        {
            fruit->Minus();
            snake->digest();
            score++;
        }
        snake->updateSnakePos();
        // view
        if (ibsc)
        {
            drawBoard();
            ibsc = false;
        }
        if (fruit->getCount() == 1)
            drawFruit(fruit);
        drawSnake(snake);
        wrefresh(board);
        // check game over
        if (snake->is_death())
            break;
    }
    delete fruit;
    delete snake;
    gameOver();
}

Game::~Game(){}


