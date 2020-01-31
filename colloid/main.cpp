#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "Particle.h"
using namespace std;
const double PI = 3.141592653589793;
// properties of the space
double  x_len    =  1.0;
double  y_len    =  1.0;
double  dt       =  0.01;
double  dtfifth  =  dt/5;
// radius
double radius = 0.02;
double dia2 = 4*radius*radius;
// boundarys for the position of the particles, for a fixed radius
double maxx = x_len - radius;
double minx = radius;
double maxy = y_len - radius;
double miny = radius;
// particle number
const int root_num = 49;
const int num = root_num*root_num;
const int tmax = 100;

// place holdes
double new_x, new_y;
double old_x, old_y;
double new_vx;
double new_vy;
double dist2;
char fileName[50];
bool overlap;

//system("makdir -pv positions");

bool check_coll(double, double, Particle);
void init(Particle (&partArr)[num]);
void update(Particle (&partArr)[num]);
void print(Particle (&partArr)[num], int);


int main()
{

    // Seed random
    srand(2);
    // Initialization
    Particle partArr [num]; // place holder array all particles are off the map
    init(partArr);
    //print(partArr, 0);
    //print(partArr, 1);
    clock_t t0;
    t0 = clock();
    for (int t=1; t<tmax; ++t) {
        //cout << "time = " << t << "\n";
        // cout << partArr[0].x << "\t" << partArr[0].y << "\t" << partArr[0].vx << "\t" << partArr[0].vy << "\n";
        update(partArr);
        // cout << partArr[0].x << "\t" << partArr[0].y << "\t" << partArr[0].vx << "\t" << partArr[0].vy << "\n";
        //print(partArr, t);
        //double ke=0;
        //for (int i=0; i<num; ++i) {
            //ke += partArr[i].vx*partArr[i].vx+partArr[i].vy*partArr[i].vy;

        //}
    }
    t0 = clock() - t0;
    printf ("%4d\t%f \n",root_num,((float)t0)/CLOCKS_PER_SEC);





    return 0;
}


void init(Particle (&partArr)[num]) {
    // evenly spaced particles in the space
    for(int i = 0; i<root_num; ++i) {
        for(int j = 0; j<root_num; ++j) {
            // cout << "particle " << i << ", "<< j << " num = "<< i*root_num + j << "\n";
            // regular spacing
            partArr[i*root_num + j].x = x_len * 1.0/(root_num ) * (double(i)+1.0/2.0);
            partArr[i*root_num + j].y = y_len * 1.0/(root_num ) * (double(j)+1.0/2.0);

            partArr[i*root_num + j].x_old = partArr[i*root_num + j].x;
            partArr[i*root_num + j].y_old = partArr[i*root_num + j].y;
            // set radius
            partArr[i*root_num + j].rad = radius;
            // randomly assign velocities
            double r1 = ((double) rand() / (RAND_MAX)) ;
            double r2 = ((double) rand() / (RAND_MAX)) ;
            double r = r1;;
            double theta = r2*2*PI;

            partArr[i*root_num + j].vx = r*cos(theta);  
            partArr[i*root_num + j].vy = r*sin(theta);
            //partArr[i*root_num + j].vx = 1;  
            //partArr[i*root_num + j].vy = 2;
            //cout << "x = " << partArr[i*root_num + j].x << "\n";
            //cout << "y = " << partArr[i*root_num + j].y << "\n";
            // cout << "vx = " << partArr[i*root_num + j].vx << "\n";
            // cout << "vy = " << partArr[i*root_num + j].vy << "\n";
        }
    }
}

void update(Particle (&partArr)[num]) {
    // move the particles one by one and check for collision with all other particles
    for(int i = 0; i<num; ++i) {
        // break one time-step into 5 smaller timesteps
        for (int itr = 0; itr<5; ++itr) {
            new_x = partArr[i].x + partArr[i].vx*dtfifth;
            new_y = partArr[i].y + partArr[i].vy*dtfifth;
            // cout << "---->pt "<<i<<" x="<< partArr[i].x << " y= "<<partArr[i].y<<"\n";
            // cout << "---->pt "<<i<<" newx="<< new_x << " newy= "<<new_y<<"\n";
            // check for boundaries, if we left the boundary flip the directions of the velocity
            bool leftbox=false;

            if ( new_x > maxx ) {
                partArr[i].vx = -partArr[i].vx; 
                leftbox=true;
            }
            if ( new_y > maxy ) {
                partArr[i].vy = -partArr[i].vy; 
                leftbox=true;
            }
            if ( new_x < minx ) {
                partArr[i].vx = -partArr[i].vx; 
                leftbox=true;
            }
            if ( new_y < miny ) {
                partArr[i].vy = -partArr[i].vy; 
                leftbox=true;
            }
            if (leftbox) { 
                // do not update the position
                continue; 
            }

            overlap=false;
            for(int j = 0; j<num; ++j) {    //check for collision with all other particles
                if (j != i ) {              //skip if it is the same particle
                    // cout << "pt "<<i<<" x="<< partArr[i].x << " y= "<<partArr[i].y<<"\n";
                    // cout << "pt "<<i<<" newx="<< new_x << " newy= "<<new_y<<"\n";
                    // cout << "pt "<<j<<" x="<< partArr[j].x << " y= "<<partArr[j].y<<"\n";
                    overlap = check_coll(new_x, new_y, partArr[j]);
                    if ( overlap == true ) {
                        // collision found, do not update the position this substep.
                        // cout << "collision found\n";
                        //Finding normal angle between two balls
                        double x1 =  partArr[i].x;
                        double x2 =  partArr[j].x;
                        double y1 =  partArr[i].y;
                        double y2 =  partArr[j].y;
                        double u1 =  partArr[i].vx;
                        double v1 =  partArr[i].vy;
                        double u2 =  partArr[j].vx;
                        double v2 =  partArr[j].vy;
                        double theta=atan2(y2-y1,x2-x1);
                        //Transforming balls velocity to normal coordinate
                        double VN1=(u1*cos(theta))+(v1*sin(theta));
                        double VT1=(-u1*sin(theta))+(v1*cos(theta));
                        double VN2=(u2*cos(theta))+(v2*sin(theta));
                        double VT2=(-u2*sin(theta))+(v2*cos(theta));
                        //Resolving colllision for normal axis
                        double VN1_F=VN2;
                        double VN2_F=VN1;
                        //Retransforming balls velocity to original coordinate
                        partArr[i].vx=(VN1_F*cos(theta))-(VT1*sin(theta));
                        partArr[i].vy=(VN1_F*sin(theta))+(VT1*cos(theta));
                        partArr[j].vx=(VN2_F*cos(theta))-(VT2*sin(theta));
                        partArr[j].vy=(VN2_F*sin(theta))+(VT2*cos(theta));

                        //partArr[i].vx = 0;
                        //partArr[i].vy = 0;
                        // stop moving and look at the next particle
                        break; //exit the current check loop and start a new particle with itr=0




                    }
                }
            }
            if ( overlap == true ) { break;}                 // stop iterating over sub dt and go to next particle
            else {
                // update to new positions
                partArr[i].x_old = partArr[i].x;    // update the old position storage
                partArr[i].y_old = partArr[i].y;
                partArr[i].x = new_x;               // update current position
                partArr[i].y = new_y;

            }
        }
        // stop_moving: cout<<"stopped_moving";// leave this loop
    }
}

void print(Particle (&partArr)[num], int time_stamp) {
    sprintf(fileName, "positions/%06d.dat", time_stamp);
    ofstream fout;
    fout.open(fileName);
    fout <<  "#         x          y\n";
    for(int i = 0; i<num; ++i) {
        fout << partArr[i].x << "\t" << partArr[i].y << "\t" << partArr[i].vx << "\t" << partArr[i].vy << "\n";
    }
    fout.close();
}

bool check_coll(double x, double y, Particle p2) {
    dist2 = (x - p2.x)*(x - p2.x) + (y - p2.y)*(y - p2.y);
    if (dist2 < dia2) {
        return true;
    }
    return false;
}


