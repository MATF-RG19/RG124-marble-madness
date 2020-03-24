#include <GL/glut.h>
#include <stdio.h>
#include "field.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "marble.hpp"


#define base_g 9.81




int gravity_on = 0;
int remainingTime =100;
int A=0;
int D=0;
int W=0;
int S=0;

/* Deklaracije callback funkcija. */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_keyReleased(unsigned char key , int x , int y);
static void on_timer(int value);

//funkcije
void camera();
void make_level(const std::string& name);

Square *field[20][20];



void make_level(const std::string& name){    
    
    std::ifstream myfile(name.c_str());
    int typeOfField, y;
    if (myfile.is_open())
    {
        for (unsigned i = 0; i<20; i++){
            for(unsigned j = 0; j<20; j++){
                myfile >> typeOfField >> y;
                if (typeOfField != 0){
                    Square *p = new Square(i,y,j,typeOfField);
                    field[i][j]=p;
                }
                else{
                    field[i][j]=nullptr;
                }
            }
        }
        myfile.close();
    }

    else std::cout << "Unable to open file"; 
}







MarbleBall ball;





int main(int argc, char **argv)
{
    make_level("level1.txt");
    
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(1500, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);


    glutIgnoreKeyRepeat(true);
    /* Registruju se callback funkcije. */
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutKeyboardUpFunc(on_keyReleased);
    
    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

    glutTimerFunc(1000, on_timer, 1);
    glutTimerFunc(20, on_timer, 2);
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_reshape(int width, int height){
    
    

    glViewport(0,0,width,height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)width/height, 1, 2000);
}


static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'g':
	case 'G':
            if(gravity_on == 0)
            {
		glutTimerFunc(100, on_timer, 0);
		gravity_on = 1;
            }
            else
            {
		gravity_on = 0;
            }
            break;
        case 27:
            exit(0);
            break;
        case 'W':
        case 'w':
            W=1;
            break;
        case 'A':
        case 'a':
            A=1;
            break;
        case 'S':
        case 's':
            S=1;
            break;
        case 'D':
        case 'd':
            D=1;
            break;
        case 'R':
        case 'r':
            {
                ball.reset();
                break;
            }
    }
    
     
}

static void on_keyReleased(unsigned char key , int x , int y ){

	
    switch(key){
        case 'W':
        case 'w':
            W=0;
            break;
         case 'A':
         case 'a':
             A=0;
             break;
        case 'S':
        case 's':
            S=0;
            break;
        case 'D':
        case 'd':
            D=0;
            break;
            
    }
}



static void on_timer(int value)
{
    if(value == 0){
    
        ball.v_y -= base_g;
        ball.y += ball.v_y;
        
        glutPostRedisplay();
        if (gravity_on == 1)
        {
            glutTimerFunc(20, on_timer, 0);
        }
    }
    
    if(value == 1){
        //TODO vreme do kraja
    }
    
    if(value == 2){
        
        ball.move(A,D,W,S);
        glutPostRedisplay();

        glutTimerFunc(20,on_timer,2);
        
    }
}

static void on_display(void)
{
    
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { 0, 0, 2000, 0 };

    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };

    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };

    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 1.0, 0.1, 0.1, 1 };

    /* Koeficijenti difuzne refleksije materijala. */
    GLfloat diffuse_coeffs[] = { 0.0, 0.0, 0.8, 1 };

    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };

    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 20;
    
    
    
    
    
    /* Brise se prethodni sadrzaj 'prozora'. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    camera();

    
    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
    
    glShadeModel(GL_SMOOTH);
    glDisable(GL_LIGHTING);
    for(unsigned i=0; i<20; i++){
        for(unsigned j = 0; j<20; j++){
            if(field[i][j]==nullptr)
                continue;
            field[i][j]->draw();
        }
        
    }
    glEnable(GL_LIGHTING);
    ball.redraw();
    
//     glPushMatrix();
//         glTranslatef(50,50,50);
//         glColor3f(1,0,0);
//         glutSolidSphere(10,10,10);
//     glPopMatrix();
//     
//     glPushMatrix();
//         glColor3f(0.5,0.5,0);
//         glTranslatef(0,-50,0);
//         glScaled(2000,1,2000);
//         glutSolidCube(1);
//     glPopMatrix();
    
    

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

void camera(){
    gluLookAt(ball.x, ball.y + 500, ball.z - 500, ball.x, ball.y, ball.z,0,1,0);
}



