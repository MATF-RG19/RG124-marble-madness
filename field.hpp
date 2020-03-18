#ifndef __field_HPP__
#define __field_HPP__

#include <GL/glut.h>
#include <stdio.h>
#include <fstream>


#include <GL/glut.h>
#include <vector>
#include <iostream>



class Square 
{
public:
    Square(double x, double y, double z,int typeOfField);
    
    void draw();
    
    
private:
    void drawEdge();
    void drawCorner();
    void drawCube();
    
    double x;
    double y;
    double z;
    double size;
    int typeOfField;
};








#endif