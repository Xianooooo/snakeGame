#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "obj.h"
#include <random>

class Fruit : public Obj
{
    public:
    Fruit(int _y = 0, int _x = 0
    , int _width = 0, int _length = 0) : Obj(_y, _x)
    {
       count = 0; 
    }
    // add fruit count
    void Add(){ count++; }
    // minus fruit count 
    void setCount(int c) { count = c; } 
    void Minus(){ count--; } 
    int getCount()const{ return count; }
    void UpdateFruitPos(int _y, int _x){ setYX( _y, _x); }
    private:
    int count;
};

#endif