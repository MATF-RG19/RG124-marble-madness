#ifndef __marble_HPP__
#define __marble_HPP__

#include <GL/glut.h>
#include <stdio.h>
#include <fstream>


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
    void redraw();
    
    void reset();
};




#endif