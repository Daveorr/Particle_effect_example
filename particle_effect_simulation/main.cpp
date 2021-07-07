//
//  main.cpp
//  particle_effect_simulation
//
//  Created by Davide Orrù on 02/07/21.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "screen.hpp"
#include "swarm.hpp"
#include "SDL.h"


int main(int argc, const char * argv[]) {
    
    time_t current_time = time(NULL);
    srand((unsigned int)current_time);
    
        
    Screen screen;
    
    if(screen.init()==false){
        std::cout << "Error Initializing SDL Lib" << std::endl;
        return 1;
    }
    
    Swarm swarm;
    
//    main render loop here:
    while(true){
        // Update Particles
        double elapsed = SDL_GetTicks();
        swarm.update(elapsed);
        // Draw Particles
        const Particle * const pParticles = swarm.getParticle();
        
        for(int i=0; i<Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];
            
            int xPosition = (pParticles[i].x_coord + 1) * Screen::SCREEN_WIDTH/2;
            int yPosition =  pParticles[i].y_coord * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;
            
            unsigned char red = (1 + sin(elapsed*0.001)) * 128;
            unsigned char green = (1 + sin(elapsed*0.002)) * 128;
            unsigned char blue = (1 + sin(elapsed*0.003)) * 128;
            
            screen.setPixel(xPosition, yPosition, red, green, blue);
        }
        //  apply blur
        screen.boxBlur();
        
        // Update screen
        screen.update();
        // Check for messages/events
        if(screen.processEvents()==false){
            break;
        }
    }
    screen.close();
    return 0;
}
