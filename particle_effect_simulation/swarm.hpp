//
//  swarm.hpp
//  particle_effect_simulation
//
//  Created by Davide Orrù on 06/07/21.
//

#ifndef swarm_hpp
#define swarm_hpp

#include <stdio.h>
#include "particle.hpp"

class Swarm {
private:
    Particle *pParticles;
    int t0 = 0;
public:
    const static int NPARTICLES = 5000;
public:
    Swarm();
    virtual ~Swarm();
    const Particle* const getParticle() {return pParticles;};
    void update(double elapsed);
};


#endif /* swarm_hpp */
