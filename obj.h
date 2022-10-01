#ifndef _OBJ_H_
#define _OBJ_H_

#include <ncurses.h>

class Obj
{
    private:
    int boardWidth, boardLength, x, y;

    public:
    Obj(int _y = 0, int _x = 0)
    {
        x = _x;
        y = _y;
    }
    int getX()const{ return x; }
    int getY()const{ return y; }
    void setX(int _x){ x = _x; }
    void setY(int _y){ y = _y; }
    void setYX(int _y, int _x){ setX(_x); setY(_y); }
};
#endif