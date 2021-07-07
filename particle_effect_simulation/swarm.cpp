//
//  swarm.cpp
//  particle_effect_simulation
//
//  Created by Davide Orrù on 06/07/21.
//

#include "swarm.hpp"

Swarm::Swarm() {
    // create a particles array
    pParticles = new Particle[NPARTICLES];
    
}

Swarm::~Swarm() {
    delete [] pParticles;
}

void Swarm::update(double elapsed) {
    // each particle position of the swarm is updated
    
    int delta_t = (int)elapsed - t0;
    
    for(int i=0; i<Swarm::NPARTICLES; i++) {
        pParticles[i].update(delta_t);
    }
    
    t0 = elapsed; // update t0
}
