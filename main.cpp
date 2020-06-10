#include <GL/glut.h>
#include <stdio.h>
#include "field.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <math.h>
#include "marble.hpp"
#include "image.hpp"
#include <cstring>




#define FILENAME0 "game_over.bmp"
#define FILENAME1 "win.bmp"
static GLuint names[2];


//promenljive za unistavanje mape
int destructRow;
int isDestroy[20][20];
int destruction;

//parametar za pocetak igre
int beforeBegin;

//parametri kraja igre
int gameOver;
int winGame;

//vreme do kraja igre
int remainingTime;

//pocetni pogled kamere
int CamRotationAngle=180;

//paremetri kretanja
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
void makeLevel(const std::string& name);
void rotateCamera();
void initialize();
void displayTime(char *string);
void winEndScreen(int ind);

MarbleBall ball;
End end=End();
Square *field[20][20];


//ucitavnje nivoa, pocetka i starta iz datoteke i globalnih parametara
void makeLevel(const std::string& name){    
    
    
    //inicijalizacija za novi nivo
    for(unsigned i = 0; i<20; i++){
        for(unsigned j = 0; j<20; j++){
            isDestroy[i][j]=0;
        }
    }
    winGame=0;
    remainingTime=20;
    gameOver=0;
    beforeBegin=1;
    destruction=0;
    destructRow=0;
    end.empty();
    
    
    
    std::ifstream myfile(name.c_str());
    int startX, startZ;
    int endX, endZ;
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
        
    }
    else std::cout << "Unable to open file"; 
    
    
    // ucitavnje poceetne pozicije loptice
    myfile >> startX >> startZ;
    if(field[startX][startZ]){
        ball.startingPosition(startX, field[startX][startZ]->getLevel()+1, startZ);
    }
    else{
        std::cout << startX << " " <<startZ << " can't be starting position";
        exit(EXIT_FAILURE);
    }
    
    //ucitavnje polja gde je kraj
    for(unsigned i = 0; i < 6; i++){
        myfile >> endX >> endZ;
        if(!field[endX][endZ]){
            std::cout << endX << " " << endZ << " can't be end position";
            exit(EXIT_FAILURE);
        }
        end.addSquare(field[endX][endZ], endX, endZ);
    }
    
    
    
    
    myfile.close();
}







int main(int argc, char **argv)
{
    
    makeLevel("level1.txt");
    
    
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
    initialize();
    

    //pokrecu se tajmeri
    //tajmer za vereme do kraja igrice
    glutTimerFunc(1000, on_timer, 1);
    //tajmer za odziv kretanja
    glutTimerFunc(20, on_timer, 2);
    //tajmer za unistavanje mape
    glutTimerFunc(500,on_timer,3);
    
    
    
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}


//incijalizacija teksture
void initialize(){
    Image *image;

    /* Postavlja se boja pozadine. */
    glClearColor(0.75, 0.75, 0.75, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, FILENAME0);

    glGenTextures(2, names);

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    image_read(image, FILENAME1);
    
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    
    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);
}



static void on_reshape(int width, int height){
    
    

    glViewport(0,0,width,height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)width/height, 1, 2000);
}

//ulaz sa tastature
static void on_keyboard(unsigned char key, int x, int y){
    
    //beforeBegin=0;
    switch(key){
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
            ball.reset();
            break;
        case 'E':
        case 'e':
            CamRotationAngle=(CamRotationAngle+5) % 360;
            break;
        case 'Q':
        case 'q':
            CamRotationAngle=(CamRotationAngle-5) % 360;
            break;
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


//tajmeri
static void on_timer(int value)
{
    
    //meri vreme do kraja igre
    if(value == 1){
        if(!beforeBegin && remainingTime>0){
            if(!winGame)
                remainingTime--;
        }
        else if(remainingTime==0){
            gameOver=1;
            destruction=1;
            if(destructRow==20){
                destruction=0;
            }
        }
        glutTimerFunc(1000,on_timer,1);
    }
    
    //tajmer za odziv tastature
    if(value == 2){
        if(winGame || gameOver || beforeBegin){
            A=0;
            D=0;
            W=0;
            S=0;
        }
        ball.move(A,D,W,S);
        if(destructRow==20){
            destruction=0;
        }
        
        glutPostRedisplay();
        
        glutTimerFunc(20,on_timer,2);
        
    }
    
    //tajmer za unistavanje mape
    
    if(value == 3){
        if(destruction==1){
            if(winGame){
                end.empty();
                end.addSquare(field[int(ball.x/100)][int(ball.z/100)], 
                            int(ball.x/100),int(ball.z/100));
            }
            if(gameOver) end.empty();
            for(unsigned j = 0; j<20; j++)
                isDestroy[destructRow][j]=1;
            isDestroy[int(ball.x/100)][int(ball.z/100)]=0;
            destructRow++;
            if(destructRow==20){
                destruction=0;
            }
        }
        
        glutTimerFunc(300,on_timer,3);
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
        
    if(winGame && !destruction){
        winEndScreen(1);
    }else if(gameOver && !destruction){
        winEndScreen(0);
    }else{
        
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
                if(isDestroy[i][j]){
                }else{
                    field[i][j]->draw();
                }
            }
        }

        
        glEnable(GL_LIGHTING);
        ball.redraw();
        glDisable(GL_LIGHTING);
        end.draw();
        
        
        
        
        
        char time[10];
        sprintf(time, "%d", remainingTime);
        displayTime(time);

    }
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}

//postavka kamere
void camera(){
    int cameraDistance=500;
    float camX=ball.x+cameraDistance*sin(CamRotationAngle*2*M_PI/360);
    float camY=ball.y+cameraDistance;
    float camZ=ball.z+cameraDistance*cos(CamRotationAngle*2*M_PI/360);
    gluLookAt(camX, camY, camZ, ball.x, ball.y, ball.z,0,1,0);
}

//funkcija ispisuje vreme do kraja igre
void displayTime(char *string) {
	

	glColor3f( 0, 0, 1.0 );
	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, 1500, 0, 700);

		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
			glLoadIdentity();

			glRasterPos2i(10, 700-10-24);

			int len = (int)strlen(string);
			for ( int i = 0; i<len; ++i ) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
			}
		glPopMatrix();

		glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );

}

//teksture za pobedu i poraz u igrici
void winEndScreen(int ind){
    
    gluLookAt(0,0,-1,0,0,0,1,0,0);
    
     glPushMatrix();
        if(ind){
            glBindTexture(GL_TEXTURE_2D, names[1]);
            glBegin(GL_QUADS);
                glNormal3f(0, 0, 1);

                glTexCoord2f(0, 0);
                glVertex3f(-1, -1, 0);

                glTexCoord2f(1, 0);
                glVertex3f(-1, 1, 0);

                glTexCoord2f(1, 1);
                glVertex3f(1, 1, 0);

                glTexCoord2f(0, 1);
                glVertex3f(1, -1, 0);
            glEnd();
        
        
        
        glBindTexture(GL_TEXTURE_2D, 0);
        }else{
            glBindTexture(GL_TEXTURE_2D, names[0]);
            glBegin(GL_QUADS);
                glNormal3f(0, 0, 1);

                glTexCoord2f(0, 0);
                glVertex3f(-1, -1, 0);

                glTexCoord2f(1, 0);
                glVertex3f(-1, 1, 0);

                glTexCoord2f(1, 1);
                glVertex3f(1, 1, 0);

                glTexCoord2f(0, 1);
                glVertex3f(1, -1, 0);
            glEnd();
        
        
        
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
    glPopMatrix();
}

