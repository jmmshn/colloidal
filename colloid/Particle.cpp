#include <stdio.h>
#include  "Particle.h"
using namespace std;
//Particle::Particle (double x0, double y0, double vx0, double vy0) {
//    x = x0;
//    y = y0;
//    vx = vx0;
//    vy = vy0;
//}
Particle::Particle () {
    x=-100;
    y=-100;
    rad=0;
    vx=0;
    vy=0;
}


void Particle::print_data() {

    cout << "x = " << x 
        << "; y = " << y ;
    //cout << "vx = " << vx << "\n";
    //cout << "vy = " << vy << "\n";
    cout << "\n";
    return;
}

double Particle::get_dist(Particle p) {

    return x - p.x;
}
