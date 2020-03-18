#include "marble.hpp"

static int gravity_on;
MarbleBall::MarbleBall() 
{
    x = 0;
    y = 0;
    z = 0;
    v_x = 0;
    v_y = 0;
    v_z = 0;
};

void MarbleBall::redraw() {
glPushMatrix();
    glTranslatef(50,150,50);
    glColor3f(0, 0, 0);
        
    if (y < -3000)
    {
        reset();
    }
    else
    {
        glTranslatef(x, y, z);
    }
    
    if (v_x != 0) 
    {
        glRotatef(x, 0, 1, 0);
    }
    else if (v_z != 0) 
    {
        glRotatef(-z, 1, 0, 0);
    }
        
    glutSolidSphere(50,100,100);
glPopMatrix();
};
    
void MarbleBall::reset()
{
    x = 0;
    y = 0;
    z = 0;
    v_x = 0;
    v_y = 0;
    v_z = 0;
    gravity_on = 0;
}