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


struct Position{
    Position(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    int x;
    int y;
    int z;
};


//polja za kraj igre
class End{
public:
    
    ~End(){
        for(unsigned i=0; i < squares.size();i++){
            delete squares[i];
        }
    }
    
    void empty(){
        squares.clear();
        positions.clear();
    }
    
    void addSquare(Square *s, int x, int z){
        Position p = Position(x, s->getLevel()+1, z);
        positions.push_back(p);
        squares.push_back(s);
    }
    void draw();
    std::vector<Position> gameEnd(){
        return positions;
    }
private:
    std::vector<Square*> squares;
    std::vector<Position> positions;
};




#endif