//
//  screen.hpp
//  particle_effect_simulation
//
//  Created by Davide Orrù on 05/07/21.
//

#ifndef screen_hpp
#define screen_hpp

#include <stdio.h>
#include <SDL.h>

class Screen{
    
public:
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HEIGHT = 600;
    
public:
    Screen();
    
    bool init();
    bool processEvents();
    void close();
    void update();
    void setPixel(int col, int row, Uint8 red, Uint8 green, Uint8 blue);
    void clean();
    void boxBlur();
    
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Uint32 *pixelBuffer1;
    Uint32 *pixelBuffer2;

};

#endif /* screen_hpp */
