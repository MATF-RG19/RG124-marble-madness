#include "field.hpp"

Square::Square(double x, double y, double z, int typeOfField){
    this->x=100*x;
    this->y=100*y;
    this->z=100*z;
    level=y;
    this->typeOfField=typeOfField;
}

double Square::getX(){
    return x;
}

double Square::getY(){
    return y;
}

double Square::getZ(){
    return z;
}

int Square::getLevel(){
    return level;
}

int Square::getType(){
    return typeOfField;
}

void Square::drawBelow(int lvl){
    if(lvl>0)
        drawBelow(lvl-1);
    glTranslatef(0,-100,0);
    drawCube();
}

void Square::draw(){
    
    glPushMatrix();
        
        
        glTranslatef(x,y,z);
        
        glPushMatrix();
        if(level >0){
            drawBelow(level-1);
        }
        glPopMatrix();
            
            
        switch(typeOfField){
            case 1:
                drawEdge();
                break;
            case 2:
                drawCorner();
                break;
            case 3:
                glTranslatef(100,0,0);
                glRotatef(270,0,1,0);
                drawEdge();
                break;
            case 4:
                glTranslatef(100,0,0);
                glRotatef(270,0,1,0);
                drawCorner();
                break;
            case 5:
                drawCube();
                break;
            case 6:
                glTranslatef(100,0,100);
                glRotatef(180,0,1,0);
                drawCorner();
                break;
            case 7:
                glTranslatef(100,0,100);
                glRotatef(180,0,1,0);
                drawEdge();
                break;
            case 8:
                glTranslatef(0,0,100);
                glRotatef(90,0,1,0);
                drawCorner();
                break;
            case 9:
                glTranslatef(0,0,100);
                glRotatef(90,0,1,0);
                drawEdge();
                break;
        }
       
        
        
        
    glPopMatrix();
}

void Square::drawCube(){
    glPushMatrix();  
        glColor3f(0,0,0);
        //dno
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(100,0,0);
            glVertex3f(100,0,100);
            glVertex3f(0,0,100);
            glVertex3f(0,0,0);
        glEnd();
        //prednja strana
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(0,100,0);
            glVertex3f(100,100,0);
            glVertex3f(100,0,0);
            glVertex3f(0,0,0);
        glEnd();
        //zadnja strana
        glBegin(GL_POLYGON);
            glVertex3f(0,0,100);
            glVertex3f(0,100,100);
            glVertex3f(100,100,100);
            glVertex3f(100,0,100);
            glVertex3f(0,0,100);
        glEnd();
        //desna strana
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(0,0,100);
            glVertex3f(0,100,100);
            glVertex3f(0,100,0);
            glVertex3f(0,0,0);
        glEnd();
        //gornja strana
        glBegin(GL_POLYGON);
            glVertex3f(0,100,0);
            glVertex3f(0,100,100);
            glVertex3f(100,100,100);
            glVertex3f(100,100,0);
            glVertex3f(0,100,0);
        glEnd();
        //leva strana
        glBegin(GL_POLYGON);
            glVertex3f(100,0,0);
            glVertex3f(100,100,0);
            glVertex3f(100,100,100);
            glVertex3f(100,0,100);
            glVertex3f(100,0,0);
        glEnd();
        
        //okvir
        //dno
        glColor3f(1,1,1);
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(101,-1,-1);
            glVertex3f(101,-1,101);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,-1,-1);
        glEnd();
        //prednji trougao
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(-1,101,-1);
            glVertex3f(101,101,-1);
            glVertex3f(100,-1,-1);
            glVertex3f(-1,-1,-1);
        glEnd();
        //zadnji trougao
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,101,101);
            glVertex3f(101,101,101);
            glVertex3f(101,-1,101);
            glVertex3f(-1,-1,101);
        glEnd();
        //desna strana
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,101,101);
            glVertex3f(-1,101,-1);
            glVertex3f(-1,-1,-1);
        glEnd();
        //gornja strana
        glBegin(GL_LINE_STRIP);
            glVertex3f(0,101,0);
            glVertex3f(0,101,101);
            glVertex3f(101,101,101);
            glVertex3f(101,101,0);
            glVertex3f(0,101,0);
        glEnd();
        //leva strana
        glBegin(GL_LINE_STRIP);
            glVertex3f(101,-1,-1);
            glVertex3f(101,101,-1);
            glVertex3f(101,101,101);
            glVertex3f(101,-1,101);
            glVertex3f(101,-1,-1);
        glEnd();
    glPopMatrix();
}

void Square::drawEdge(){
    glPushMatrix();  
        glColor3f(0,0,0);
        //dno
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(100,0,0);
            glVertex3f(100,0,100);
            glVertex3f(0,0,100);
            glVertex3f(0,0,0);
        glEnd();
        //prednji trougao
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(0,100,0);
            glVertex3f(100,0,0);
            glVertex3f(0,0,0);
        glEnd();
        //zadnji trougao
        glBegin(GL_POLYGON);
            glVertex3f(0,0,100);
            glVertex3f(0,100,100);
            glVertex3f(100,0,100);
            glVertex3f(0,0,100);
        glEnd();
        //desna strana
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(0,0,100);
            glVertex3f(0,100,100);
            glVertex3f(0,100,0);
            glVertex3f(0,0,0);
        glEnd();
        //gornja strana
        glBegin(GL_POLYGON);
            glVertex3f(0,100,0);
            glVertex3f(0,100,100);
            glVertex3f(100,0,100);
            glVertex3f(100,0,0);
            glVertex3f(0,0,0);
        glEnd();
        
        
        //okvir
        //dno
        glColor3f(1,1,1);
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(101,-1,-1);
            glVertex3f(101,-1,101);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,-1,-1);
        glEnd();
        //prednji trougao
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(-1,101,-1);
            glVertex3f(100,-1,-1);
            glVertex3f(-1,-1,-1);
        glEnd();
        //zadnji trougao
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,101,101);
            glVertex3f(101,-1,101);
            glVertex3f(-1,-1,101);
        glEnd();
        //desna strana
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,101,101);
            glVertex3f(-1,101,-1);
            glVertex3f(-1,-1,-1);
        glEnd();
        //gornja strana
        glBegin(GL_LINE_STRIP);
            glVertex3f(0,101,0);
            glVertex3f(0,101,101);
            glVertex3f(101,0,101);
            glVertex3f(101,0,0);
            glVertex3f(0,0,0);
        glEnd();
    glPopMatrix();
}


void Square::drawCorner(){
    glPushMatrix();  
        //dno
        glColor3f(0,0,0);
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(100,0,0);
            glVertex3f(100,0,100);
            glVertex3f(0,0,100);
            glVertex3f(0,0,0);
        glEnd();
        //prednji trougao
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(0,100,0);
            glVertex3f(100,0,0);
            glVertex3f(0,0,0);
        glEnd();
        //desni trougao
        glBegin(GL_POLYGON);
            glVertex3f(0,0,0);
            glVertex3f(0,100,0);
            glVertex3f(0,0,100);
            glVertex3f(0,0,0);
        glEnd();
        //gornja strana
        glBegin(GL_POLYGON);
            glVertex3f(0,100,0);
            glVertex3f(0,0,100);
            glVertex3f(100,0,100);
            glVertex3f(100,0,0);
            glVertex3f(0,100,0);
        glEnd();
        
        //dno
        
        glColor3f(1,1,1);
        //dno
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(101,-1,-1);
            glVertex3f(101,-1,101);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,-1,-1);
        glEnd();
        //prednji trougao
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(0,101,0);
            glVertex3f(101,-1,-1);
            glVertex3f(-1,-1,-1);
        glEnd();
        //desni trougao
        glBegin(GL_LINE_STRIP);
            glVertex3f(-1,-1,-1);
            glVertex3f(0,101,0);
            glVertex3f(-1,-1,101);
            glVertex3f(-1,-1,-1);
        glEnd();
        //gornja strana
        glBegin(GL_LINES);
            glVertex3f(-1,+101,-1);
            glVertex3f(+101,-1,+101);
        glEnd();
    glPopMatrix();
}





