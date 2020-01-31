#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <string.h>
#include <time.h>
using namespace std;

class Particle
{
    public:
        double  x,y;            //  current  positions
        double  x_old,y_old;    //  old      positions
        double  vx,vy;          //  current  velocity
        //double  vx_old,vy_old;  //  old      velocity
        double  rad;
        //(Cons/Dis)tructors
        Particle();
        Particle(double);
        //~Particle(); // number of particles does not change
        void print_data();
        double get_dist(Particle);
    private:

};

