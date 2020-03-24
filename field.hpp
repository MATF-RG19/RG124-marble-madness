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
    int nesto();
    int getLevel();
    double getX();
    double getY();
    double getZ();
    int getType();
    
private:
    void drawEdge();
    void drawCorner();
    void drawCube();
    void drawBelow(int level);
    
   
    double x;
    double y;
    double z;
    int level;
    int typeOfField;
};










#endif