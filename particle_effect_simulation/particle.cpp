//
//  particle.cpp
//  particle_effect_simulation
//
//  Created by Davide Orrù on 06/07/21.
//

#include "particle.hpp"
#include <math.h>
#include <stdlib.h>

Particle::Particle(): x_coord(0), y_coord(0) {
    init();
}

Particle::~Particle() {
    
}

void Particle::init(){
    
    x_coord = 0;
    y_coord = 0;
    
    direction = (2 * M_PI * rand())/RAND_MAX;  // angle in radians
    speed = (0.04 * rand())/RAND_MAX;
    speed *= speed;
}

void Particle::update(double delta_t) {
    // vortex effect
    direction += delta_t*0.0003;
    
    // polar coordinates
    double xspeed = speed * cos(direction);
    double yspeed = speed * sin(direction);
    // constant motion
    x_coord += xspeed * delta_t;
    y_coord += yspeed * delta_t;
    // re-init particle outside screen
    if(x_coord<-1 || x_coord>1 || y_coord<-1 || y_coord>1){
        init();
    }
    if(rand() < RAND_MAX/100){
        init();
    }
}
