#ifndef __marble_HPP__
#define __marble_HPP__

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "field.hpp"
#include <math.h>


class MarbleBall
{
public:
    double x;
    double y;
    double z;
    double v_x;
    double v_y;
    double v_z;

    
    MarbleBall();
    void move(int A,int D,int W, int S);
    void redraw();
    void reset();
    void colision(int A, int D, int W, int S);
    void startingPosition(int x, int y, int z);
    void gameEnd();
private:
    int radius;
    int position_x;
    int position_y;
    int position_z;
};




#endif