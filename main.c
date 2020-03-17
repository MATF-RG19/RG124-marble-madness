#include <GL/glut.h>
#include <stdio.h>
#include "field.cpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#define FWD 1
#define LEFT 3
#define BACK 2
#define RIGHT 4
#define base_g 9.81
#define base_a 5

static int gravity_on = 0;

/* Deklaracije callback funkcija. */
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
//static void on_keyReleased(unsigned char key , int x , int y);
static void on_timer(int value);

//funkcije
void marble(double x, double y, double z);
void plain();
void camera();
void end();

void move(int direction);

std::vector<Square*> *level = new std::vector<Square*>;

void make_level(const std::string& name){    
    std::string line;
    std::ifstream myfile(name.c_str());
    double dx, dy,dz,dsize;
    if (myfile.is_open())
    {
        while(!myfile.eof()){
            myfile >> dx >> dy >> dz >> dsize;
            level->push_back(new Flat(dx,dy,dz,dsize));
        }
        myfile.close();
    }

    else std::cout << "Unable to open file"; 

}



class MarbleBall
{
public:
    double x;
    double y;
    double z;
    double v_x;
    double v_y;
    double v_z;
    
    MarbleBall() 
    {
        x = 0;
        y = 0;
        z = 0;
        v_x = 0;
        v_y = 0;
        v_z = 0;
    };
    void redraw() { marble(x, y, z); };
    void reset()
    {
        x = 0;
        y = 0;
        z = 0;
        v_x = 0;
        v_y = 0;
        v_z = 0;
        gravity_on = 0;
    }
};

MarbleBall ball;

static int window_width, window_height;
float x=0;
float y=0;
float speed=1;

void applyAcc(double amp, int x, int y, int z)
{
    
}

int main(int argc, char **argv)
{
    make_level("1.txt");
    
    
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /* Kreira se prozor. */
    glutInitWindowSize(1500, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);


    
    /* Registruju se callback funkcije. */
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    //glutKeyboardUpFunc(on_keyReleased);
    
    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0.75, 0.75, 0.75, 0);
    glEnable(GL_DEPTH_TEST);

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_reshape(int width, int height){
    
    
    window_width = width;
    window_height = height;
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
            move(FWD);
            break;
        case 'A':
        case 'a':
            move(LEFT);
            break;
        case 'S':
        case 's':
            move(BACK);
            break;
        case 'D':
        case 'd':
            move(RIGHT);
            break;
        case 'R':
        case 'r':
            {
                ball.reset();
                break;
            }
            
    }
    
    glutPostRedisplay();
}
/*
static void on_keyReleased(unsigned char key , int x , int y ){

	std::cout << " onKeyRealeased " << std::endl; 
    switch(key){
        case 'W':
        case 'w':
            speed -= 1;
            break;
         case 'A':
         case 'a':
             speed -= 1;
             break;
        case 'S':
        case 's':
            speed = 1;
            break;
        case 'D':
        case 'd':
            speed = 1;
            break;
            
    }
}
*/
void move(int direction){
    //std::cout << "move" << std::endl;

    
    switch(direction)
    {
        case FWD:
        {
            ball.v_x = 0;
            ball.v_y = (ball.v_y < 0) ? 0 : ball.v_y;
            ball.v_y += base_a;
            ball.v_y = ball.v_y >= 15 ? 15 : ball.v_y;
            ball.y += ball.v_y;
            break;
	}
        case BACK:
        {
            ball.v_x = 0;
            ball.v_y = (ball.v_y > 0) ? 0 : ball.v_y;
            ball.v_y -= base_a;
            ball.v_y = ball.v_y <= -15 ? -15 : ball.v_y;
            ball.y += ball.v_y;
            break;
	}
        case RIGHT:
        {
            ball.v_y = 0;
            ball.v_x = (ball.v_x < 0) ? 0 : ball.v_x;
            ball.v_x += base_a;
            ball.v_x = ball.v_x >= 15 ? 15 : ball.v_x;
            ball.x += ball.v_x;
            break;
	}
        case LEFT:
        {
            ball.v_y = 0;
            ball.v_x = (ball.v_x > 0) ? 0 : ball.v_x;
            ball.v_x -= base_a;
            ball.v_x = ball.v_x <= -15 ? -15 : ball.v_x;
            ball.x += ball.v_x;
            break;
	}
    }
    
}

static void on_timer(int value)
{
    if(value != 0) return;
    
    ball.v_z -= base_g;
    ball.z += ball.v_z;
    
    glutPostRedisplay();
    if (gravity_on == 1)
    {
        glutTimerFunc(100, on_timer, 0);
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
    for(unsigned i=0; i<level->size(); i++){
        (*level)[i]->draw();
    }
    glEnable(GL_LIGHTING);
    ball.redraw();
    
    glPushMatrix();
        glTranslatef(50,50,50);
        glColor3f(1,0,0);
        glutSolidSphere(10,10,10);
    glPopMatrix();
    
    glPushMatrix();
        glColor3f(0.5,0.5,0);
        glTranslatef(0,0,-50);
        glScaled(2000,2000,1);
        glutSolidCube(1);
    glPopMatrix();
    
    

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

void camera(){
    gluLookAt(ball.x - 200, ball.y - 200, ball.z + 500, ball.x, ball.y, ball.z,0,0,1);
}


void marble(double x, double y, double z){
    glPushMatrix();
        glColor3f(0, 0, 0);
        
        if (z < -3000)
        {
            ball.reset();
        }
        else
        {
            glTranslatef(x, y, z);
        }
        
        if (ball.v_x != 0) 
        {
            glRotatef(x, 0, 1, 0);
        }
        else if (ball.v_y != 0) 
        {
            glRotatef(-y, 1, 0, 0);
        }
        
        glutSolidSphere(50,100,100);
        /*
        glTranslatef(0,0,45);
        glColor3f(0,0,1);
        glutSolidSphere(10,10,10);
        glTranslatef(0,0,-45);
        
        glTranslatef(0,45,0);
        glColor3f(0,1,0);
        glutSolidSphere(10,10,10);
        glTranslatef(0,-45,0);
        
        glTranslatef(45,0,0);
        glColor3f(1,0,0);
        glutSolidSphere(10,10,10);
        glTranslatef(-45,0,0);
        */
    glPopMatrix();
}
