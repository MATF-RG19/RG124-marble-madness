#include "marble.hpp"

#define MAX_SPEED 12
#define PI 3.141592
#define gravity 9.81

extern int winGame;
extern Square *field[20][20];
extern End end;
int ballBreak =0;
int break_animation = 0;



MarbleBall::MarbleBall() 
{
    x = 0;
    y = 0;
    z = 0;
    v_x = 0;
    v_y = -gravity;
    v_z = 0;
    radius = 45;
    position_x = 0;
    position_z = 0;
    position_y = 0;
};

void MarbleBall::startingPosition(int x, int y, int z){
    this->x = 100*x+radius;
    this->y = 100*y+radius;
    this->z = 100*z+radius;
}

void MarbleBall::redraw() {
    if(break_animation==1){
        glTranslatef(x,y,z);
        glutSolidCube(100);
    }else{
        glPushMatrix();
            glColor3f(0, 0, 0);
                
            if (y < -1000)
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
                
            glutSolidSphere(radius,100,100);
        glPopMatrix();
    }
};
    
void MarbleBall::reset()
{
    x = 45;
    y = 145;
    z = 45;
    position_x=0;
    position_y=1;
    position_z=0;
    v_x = 0;
    v_y = -gravity;
    v_z = 0;
}

void MarbleBall::move(int A,int D,int W, int S){
    
        if(position_x>19 || position_x <0 || position_z >19 || position_z<0){
            A=0;
            D=0;
            W=0;
            S=0;
        }
        
        //kretanje levo
        if(A==1){
            v_x+=0.2;
            if(v_x>=MAX_SPEED)
                v_x=MAX_SPEED;
        }
        if(A==0 && v_x>0){
            v_x-=0.3;
            if(v_x<=0)
                v_x=0;
        }
        //kretanje desno
        if(D==1){
            v_x-=0.2;
            if(v_x<=-MAX_SPEED)
                v_x=-MAX_SPEED;
        }
        if(D==0 && v_x <0){
            v_x+=0.3;
            if(v_x>=0)
                v_x=0;
        }
        //kretanje napred
        if(W==1){
            v_z+=0.2;
            if(v_z>=MAX_SPEED)
                v_z=MAX_SPEED;
        }
        if(W==0 && v_z>0){
            v_z-=0.3;
            if(v_z<=0)
                v_z=0;
        }
        //kretanje nazad
        if(S==1){
            v_z-=0.2;
            if(v_z<=-MAX_SPEED)
                v_z=-MAX_SPEED;
        }
        if(S==0 && v_z<0){
            v_z+=0.3;
            if(v_z>=0)
                v_z=0;
        }
        
        v_y=-gravity;
        
        colision(A,D,W,S);
        
        if(winGame){
            v_x=v_x*3/4;
            v_z=v_z*3/4;
        }
        
        x+=v_x;
        y+=v_y;
        z+=v_z;
        
        position_x = int(x / 100);
        if(x<0) position_x = -1;
        position_y = int(y / 100);
        if(y<0) position_y=-1;
        position_z = int(z / 100);
        if(z<0) position_z = -1;
        
        gameEnd();
        
}

void MarbleBall::colision(int A,int D,int W, int S){
    double newX;
    double newY;
    double newZ;
    double fieldX;
    double fieldY;
    double fieldZ;
    int fieldType;
    
    
    if(position_x<=19 && position_x >= 0 && position_z <=19 && position_z >= 0) v_y=0;
    
    
    //padanje levo
    if(position_x > 19){
        fieldX= field[19][position_z]->getX()+100;
        fieldY= field[19][position_z]->getY()+100;
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(newX<fieldX && newY>fieldY){
                    if(v_x == 0)
                        v_x=(newY/fieldY*2);
                    v_y=-newY/fieldY;
                }
                
            }
        }
    }
    //padanje desno
    if(position_x < 0){
        fieldX= field[0][position_z]->getX();
        fieldY= field[0][position_z]->getY()+100;
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(newX>fieldX && newY>fieldY){
                    if(v_x == 0)
                        v_x=-(newY/fieldY*2);
                    v_y=-newY/fieldY;
                }
            }
        }
    }
    //padanje gore
    if(position_z > 19){
        fieldY= field[position_x][19]->getY()+100;
        fieldZ= field[position_x][19]->getZ()+100;
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(newZ<fieldZ && newY>fieldY){
                    if(v_z == 0)
                        v_z=(newY/fieldY*2);
                    v_y=-newY/fieldY;
                }
            }
        }
    }
    //padanje dole
    if(position_z < 0){
        fieldY= field[position_x][0]->getY()+100;
        fieldZ= field[position_x][0]->getZ();
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(newZ>fieldZ && newY>fieldY){
                    if(v_z == 0)
                        v_z=-(newY/fieldY*2);
                    v_y=-newY/fieldY;
                }
            }
        }
    }
    
    
    
    
    
    
    
    
    
    
    if(position_x<20 && position_x>=0 && position_z<20 && position_z>=0){
    
        //ponasanje ako naidje na polje koje ne postoji
        if(!field[position_x][position_z]){
            v_y=-gravity;
            //ako postoji kocka sa leve strane
            if(field[position_x+1][position_z]){
                fieldX= field[position_x+1][position_z]->getX();
                fieldY= field[position_x+1][position_z]->getY()+100;
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newX>fieldX && newY>fieldY){
                            if(v_x == 0)
                                v_x=-(newY/fieldY*2);
                            v_y=-newY/fieldY;
                        }
                    }
                }
            }
            //ako postoji kocka sa desne strarne
            if(field[position_x-1][position_z]){
                fieldX= field[position_x-1][position_z]->getX()+100;
                fieldY= field[position_x-1][position_z]->getY()+100;
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newX<fieldX && newY>fieldY){
                            if(v_x == 0)
                                v_x=(newY/fieldY*2);
                            v_y=-newY/fieldY;
                        }
                        
                    }
                }
            }
            //ako postoji kocka sa gornje strane
            if(field[position_x][position_z+1]){
                fieldY= field[position_x][position_z+1]->getY()+100;
                fieldZ= field[position_x][position_z+1]->getZ();
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newZ>fieldZ && newY>fieldY){
                            if(v_z == 0)
                                v_z=-(newY/fieldY*2);
                            v_y=-newY/fieldY;
                        }
                    }
                }
            }
            //ako postoji kocka sa donje strane
            if(field[position_x][position_z-1]){
                fieldY= field[position_x][position_z-1]->getY()+100;
                fieldZ= field[position_x][position_z-1]->getZ()+100;
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newZ<fieldZ && newY>fieldY){
                            if(v_z == 0)
                                v_z=(newY/fieldY*2);
                            v_y=-newY/fieldY;
                        }
                    }
                }
            }
        }
        else{
            //zavisno od polja kako se krece na gore
            int fieldType=field[position_x][position_z]->getType();
            //levo uzbrdo
            if(v_x>0 && (fieldType==4 || fieldType==6 || fieldType == 7)){
                v_x*=0.9;
                v_y=v_x;
            }
            //desno nizbrdo
            if(v_x<0 && (fieldType==4 || fieldType==6 || fieldType == 7)){
                v_x*=1.1;
                v_y=v_x;
            }
            //levo nizbrdo
            if(v_x>0 && (fieldType==2 || fieldType==1 || fieldType==8)){
                v_x*=1.1;
                v_y=-v_x/1.1*0.9;
            }
            //desno uzbrdo
            if(v_x<0 && (fieldType==2 || fieldType==1 || fieldType == 8)){
                v_x*=0.9;
                v_y=-v_x/0.9*1.1;
            }
            //pravo uzbrdo
            if(v_z>0 && (fieldType==8 || fieldType==9 || fieldType == 6)){
                v_z*=0.9;
                if(field[position_x][position_z]->getY()+z-position_z*100+45>y){
                    v_y=v_z;
                }
            }
            //pravo nizbrdo
            if(v_z<0 && (fieldType==8 || fieldType==9 || fieldType == 6)){
                v_z*=1.1;
                v_y=v_z;
            }
            //pravo nizbrdo
            if(v_z>0 && (fieldType==2 || fieldType==3 || fieldType==4)){
                v_z*=1.1;
                v_y=-v_z/1.1*0.9;
            }
            //pravo uzbrdoo
            if(v_z<0 && (fieldType==2 || fieldType==3 || fieldType == 4)){
                v_z*=0.9;
                v_y=-v_z/0.9*1.1;
            }
            
            //padanje lopte sa vise od jednog polja visine
            if(field[position_x][position_z]->getLevel()<position_y){
                fieldY = field[position_x][position_z]->getY()+100+45;
                if(y>=fieldY){
                    v_y=-gravity;
                }
            }
        }
        
    }
    
    
    
    
    
    
    
    
    
    
    

    //kolizija u levo
    if(A && position_x < 19 && field[position_x+1][position_z] 
        && field[position_x+1][position_z]->getLevel()>=position_y){
        fieldX = field[position_x+1][position_z]->getX();
        fieldY = field[position_x+1][position_z]->getY();
        fieldZ = field[position_x+1][position_z]->getZ();
        fieldType = field[position_x+1][position_z]->getType();
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(fieldType!=4 && fieldType!=7 && fieldType!=6){
                    if(newX>=fieldX){
                        v_x=-v_x*99/100;
                    }
                }
            }
        }
    }
    else {
        if(A && position_z < 19 && position_x < 19 
            && field[position_x+1][position_z+1] 
            && field[position_x+1][position_z+1]->getLevel()>=position_y){
            fieldX= field[position_x+1][position_z+1]->getX();
            fieldZ= field[position_x+1][position_z+1]->getZ();
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newX>fieldX && newZ>fieldZ){
                        v_x=(z/fieldZ);
                        v_z=-(z/fieldZ);
                    }
                }
            }
        }
        if(A && position_z>0 && position_x < 19 
            && field[position_x+1][position_z-1] 
            && field[position_x+1][position_z-1]->getLevel()>=position_y){
            fieldX= field[position_x+1][position_z-1]->getX();
            fieldZ= field[position_x+1][position_z-1]->getZ()+100;
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newX>fieldX && newZ<fieldZ){
                        v_x=(z/fieldZ);
                        v_z=(z/fieldZ);
                    }
                }
            }
        }
    }
    
    //kolizija u desno
    if(D && position_x>0 && field[position_x-1][position_z] 
        && field[position_x-1][position_z]->getLevel()>=position_y){
        fieldX= field[position_x-1][position_z]->getX()+100;
        fieldZ= field[position_x-1][position_z]->getZ();
        fieldType = field[position_x-1][position_z]->getType();
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(fieldType!=2 && fieldType!=1 && fieldType!=8){
                    if(newX<=fieldX){
                        v_x=-v_x*99/100;
                    }
                }
            }
        }
    }
    else{
        if(D && position_z<19 && position_x>0 && field[position_x-1][position_z+1] 
            && field[position_x-1][position_z+1]->getLevel()>=position_y){
            fieldX= field[position_x-1][position_z+1]->getX()+100;
            fieldZ= field[position_x-1][position_z+1]->getZ();
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newX<fieldX && newZ>fieldZ){
                        v_x=-(z/fieldZ);
                        v_z=-(z/fieldZ);
                    }
                }
            }
        }
        if(D && position_z>0 && position_x>0 && field[position_x-1][position_z-1] 
            && field[position_x-1][position_z-1]->getLevel()>=position_y){
            fieldX= field[position_x-1][position_z-1]->getX()+100;
            fieldZ= field[position_x-1][position_z-1]->getZ()+100;
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newX<fieldX && newZ<fieldZ){
                        v_x=-(z/fieldZ);
                        v_z=(z/fieldZ);
                    }
                }
            }
        }
    }
    
    //kolizija u napred
    if(W && position_z<19 && field[position_x][position_z+1] 
        && field[position_x][position_z+1]->getLevel()>=position_y){
        fieldX= field[position_x][position_z+1]->getX();
        fieldZ= field[position_x][position_z+1]->getZ();
        fieldType = field[position_x][position_z+1]->getType();
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(fieldType!=8 && fieldType!=9 && fieldType!=6){
                    if(newZ>=fieldZ){
                        v_z=-v_z*99/100;
                    }
                }
            }
        }
        
    }
    else {
        if(W && position_x<19 && position_z<19 && field[position_x+1][position_z+1] 
            && field[position_x+1][position_z+1]->getLevel()>=position_y){
            fieldX= field[position_x+1][position_z+1]->getX();
            fieldZ= field[position_x+1][position_z+1]->getZ();
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newZ>fieldZ && newX>fieldX){
                        v_x=-(z/fieldZ);
                        v_z=(z/fieldZ);
                    }
                }
            }
        }
        if(W && position_x>0 && position_z<19 && field[position_x-1][position_z+1] 
            && field[position_x-1][position_z+1]->getLevel()>=position_y){
            fieldX= field[position_x-1][position_z+1]->getX()+100;
            fieldZ= field[position_x-1][position_z+1]->getZ();
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newZ>fieldZ && newX<fieldX){
                        v_x=(z/fieldZ);
                        v_z=(z/fieldZ);
                    }
                }
            }
        }
    }
        
    //kolizija na nazad
    if(S && position_z>0 && field[position_x][position_z-1] 
        && field[position_x][position_z-1]->getLevel()>=position_y){
        fieldX= field[position_x][position_z-1]->getX();
        fieldZ= field[position_x][position_z-1]->getZ()+100;
        fieldType = field[position_x][position_z-1]->getType();
        for(double teta = 0; teta<=PI; teta+=PI/20){
            for(double fi =0; fi<=2*PI; fi+=PI/20){
                newX = radius*sin(teta)*cos(fi)+x;
                newY = radius*cos(fi)+y;
                newZ = radius*sin(teta)*sin(fi)+z;
                if(fieldType!=2 && fieldType!=3 && fieldType!=4){
                    if(newZ<=fieldZ){
                        v_z=-v_z*99/100;
                    }
                }
            }
        }
    }
    else{ 
        if(S && position_x<19 && position_z>0 && field[position_x+1][position_z-1] 
            && field[position_x+1][position_z-1]->getLevel()>=position_y){
            fieldX= field[position_x+1][position_z-1]->getX();
            fieldZ= field[position_x+1][position_z-1]->getZ()+100;
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newZ<fieldZ && newX>fieldX){
                        v_x=-(z/fieldZ);
                        v_z=-(z/fieldZ);
                    }
                }
            }
        }
        if(S && position_x>0 && position_z>0 && field[position_x-1][position_z-1] 
            && field[position_x-1][position_z-1]->getLevel()>=position_y){
            fieldX= field[position_x-1][position_z-1]->getX()+100;
            fieldZ= field[position_x-1][position_z-1]->getZ()+100;
            for(double teta = 0; teta<=PI; teta+=PI/20){
                for(double fi =0; fi<=2*PI; fi+=PI/20){
                    newX = radius*sin(teta)*cos(fi)+x;
                    newY = radius*cos(fi)+y;
                    newZ = radius*sin(teta)*sin(fi)+z;
                    if(newZ<fieldZ && newX<fieldX){
                        v_x=(z/fieldZ);
                        v_z=-(z/fieldZ);
                    }
                }
            }
        }
    }
    
    
}



void MarbleBall::gameEnd(){
    std::vector<Position> p=end.gameEnd();
    for(unsigned i=0; i <p.size(); i++){
        
        if(p[i].x==position_x && p[i].y==position_y && p[i].z==position_z){
            std::cout << "game win!" << std::endl;
            winGame = 1;
        }
    }
}
    
    
