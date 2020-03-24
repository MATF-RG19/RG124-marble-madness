#include "marble.hpp"

#define MAX_SPEED 12
#define PI 3.141592

extern int gravity_on;
extern Square *field[20][20];


MarbleBall::MarbleBall() 
{
    x = 50;
    y = 150;
    z = 50;
    v_x = 0;
    v_y = 0;
    v_z = 0;
    radius = 45;
    position_x = 0;
    position_z = 0;
    position_y = 0;
};

void MarbleBall::redraw() {
    glPushMatrix();
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
            
        glutSolidSphere(radius,100,100);
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

void MarbleBall::move(int A,int D,int W, int S){
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
        
        colision(A,D,W,S);
        
        z+=v_z;
        x+=v_x;
        
        position_x = int(x / 100);
        position_y = int(y / 100);
        position_z = int(z / 100);
}

void MarbleBall::colision(int A,int D,int W, int S){
// //     std::cout << "x: " << position_x << " y: " << position_y << " z: " << position_z << std::endl;
    double newX;
    double newY;
    double newZ;
    double fieldX;
    double fieldY;
    double fieldZ;
    int fieldType;
    
    if(A && position_x == 19) return;
    if(D && position_x == 0) return;
    if(W && position_z == 19) return;
    if(S && position_z == 0) return;
    
    if(position_x > 0 && position_x < 19 && position_z > 0 && position_z<19){
        //kolizija u levo
        if(A && field[position_x+1][position_z]){
            fieldX = field[position_x+1][position_z]->getX();
            fieldZ = field[position_x+1][position_z]->getZ();
            fieldType = field[position_x+1][position_z]->getType();
            if(field[position_x+1][position_z]->getLevel()>=position_y){
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newX>=fieldX){
                            v_x=-v_x*99/100;
                        }
                    }
                }
            }
        }
        if(A && field[position_x+1][position_z+1]){
            fieldX= field[position_x+1][position_z+1]->getX();
            fieldZ= field[position_x+1][position_z+1]->getZ();
            if(field[position_x+1][position_z+1]->getLevel()>=position_y){
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
        }
        if(A && field[position_x+1][position_z-1]){
            fieldX= field[position_x+1][position_z-1]->getX();
            fieldZ= field[position_x+1][position_z-1]->getZ()+100;
            if(field[position_x+1][position_z-1]->getLevel()>=position_y){
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
        if(D && field[position_x-1][position_z]){
            fieldX= field[position_x-1][position_z]->getX()+100;
            fieldZ= field[position_x-1][position_z]->getZ();
            if(field[position_x-1][position_z]->getLevel()>=position_y){
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newX<=fieldX){
                            v_x=-v_x*99/100;
                        }
                    }
                }
            }
        }
        if(D && field[position_x-1][position_z+1]){
            fieldX= field[position_x-1][position_z+1]->getX()+100;
            fieldZ= field[position_x-1][position_z+1]->getZ();
            if(field[position_x-1][position_z+1]->getLevel()>=position_y){
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
        }
        if(D && field[position_x-1][position_z-1]){
            fieldX= field[position_x-1][position_z-1]->getX()+100;
            fieldZ= field[position_x-1][position_z-1]->getZ()+100;
            if(field[position_x-1][position_z-1]->getLevel()>=position_y){
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
        if(W && field[position_x][position_z+1]){
            fieldX= field[position_x][position_z+1]->getX();
            fieldZ= field[position_x][position_z+1]->getZ();
            if(field[position_x][position_z+1]->getLevel()>=position_y){
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newZ>=fieldZ){
                            v_z=-v_z*99/100;
                        }
                    }
                }
            }
        }
        if(W && field[position_x+1][position_z+1]){
            fieldX= field[position_x+1][position_z+1]->getX();
            fieldZ= field[position_x+1][position_z+1]->getZ();
            if(field[position_x+1][position_z+1]->getLevel()>=position_y){
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
        }
        if(W && field[position_x-1][position_z+1]){
            fieldX= field[position_x-1][position_z+1]->getX()+100;
            fieldZ= field[position_x-1][position_z+1]->getZ();
            if(field[position_x-1][position_z+1]->getLevel()>=position_y){
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
        if(S && field[position_x][position_z-1]){
            fieldX= field[position_x][position_z-1]->getX();
            fieldZ= field[position_x][position_z-1]->getZ()+100;
            if(field[position_x][position_z-1]->getLevel()>=position_y){
                for(double teta = 0; teta<=PI; teta+=PI/20){
                    for(double fi =0; fi<=2*PI; fi+=PI/20){
                        newX = radius*sin(teta)*cos(fi)+x;
                        newY = radius*cos(fi)+y;
                        newZ = radius*sin(teta)*sin(fi)+z;
                        if(newZ<=fieldZ){
                            v_z=-v_z*99/100;
                        }
                    }
                }
            }
        }
        if(S && field[position_x+1][position_z-1]){
            fieldX= field[position_x+1][position_z-1]->getX();
            fieldZ= field[position_x+1][position_z-1]->getZ()+100;
            if(field[position_x+1][position_z-1]->getLevel()>=position_y){
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
        }
        if(S && field[position_x-1][position_z-1]){
            fieldX= field[position_x-1][position_z-1]->getX()+100;
            fieldZ= field[position_x-1][position_z-1]->getZ()+100;
            if(field[position_x-1][position_z-1]->getLevel()>=position_y){
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
    
 
    
    
    
        
}

    
    
