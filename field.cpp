#include <GL/glut.h>

class Square 
{
public:
    virtual void draw() = 0;
    Square(double x, double y, double z, double size){
        this->x=x;
        this->y=y;
        this->z=z;
        this->size=size;
    }
protected:
    double x;
    double y;
    double z;
    double size;
};

class Flat : public Square
{
public:
    Flat(double x, double y, double z, double size)
        :Square(x,y,z,size)
    {}
    void draw(){
        glPushMatrix();
            glColor3f(0.3,0.3,0.3);
            glTranslatef(x,y,z);
            glScaled(size,size,10);
            glutSolidCube(1);
        glPopMatrix();
    }
private:
        
};
