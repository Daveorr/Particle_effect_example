//
//  particle.hpp
//  particle_effect_simulation
//
//  Created by Davide Orrù on 06/07/21.
//

#ifndef particle_hpp
#define particle_hpp

#include <stdio.h>

class Particle {
public:
    double x_coord;
    double y_coord;
    double speed;
    double direction;
public:
    Particle();
    virtual ~Particle();
    void update(double elapsed);
    void init();
};

#endif /* particle_hpp */
