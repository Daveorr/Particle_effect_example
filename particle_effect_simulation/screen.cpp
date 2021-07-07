//
//  screen.cpp
//  particle_effect_simulation
//
//  Created by Davide Orrù on 05/07/21.
//

#include "screen.hpp"

Screen::Screen() : window(NULL), renderer(NULL), texture(NULL), pixelBuffer1(NULL), pixelBuffer2(NULL){
}

bool Screen::init(){
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }
    //    deploy SDL window, renderer and texture
    window = SDL_CreateWindow("Particle Effect", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    texture =  SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

    //    deploy screen buffers (we need 2 for blurring)
    pixelBuffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
    pixelBuffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

    memset(pixelBuffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
    memset(pixelBuffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

    //    pointer guarding
    if(window==NULL){
        SDL_Quit();
        return false;
    }
    if(renderer==NULL){
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    if(texture==NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    for(int i=0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++){
        pixelBuffer1[i] = 0x00000000; // set black screen
        pixelBuffer2[i] = 0x00000000; // set black screen

    }
    return true;
}

void Screen::setPixel(int col, int row, Uint8 red, Uint8 green, Uint8 blue){
    
    // discard particles that are out of the screen
    if(col<0 || col>= SCREEN_WIDTH || row<0 || row>=SCREEN_HEIGHT){
        return;
    }
    
    Uint32 color = 0;
    // bit shifting  RGB
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    //  this will draw a single pixel in the canvas at (xy) = (row, col)
    pixelBuffer1[(row*SCREEN_WIDTH + col)] = color;
    pixelBuffer2[(row*SCREEN_WIDTH + col)] = color;
}

void Screen::update(){
    SDL_UpdateTexture(texture, NULL, pixelBuffer1, SCREEN_WIDTH*sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bool Screen::processEvents(){
    SDL_Event event;
    //      event polling loop
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    return false;;
                }
            }
    return true;
}

void Screen::boxBlur(){
    // blur is not pixelwise but applied to the frame
    // Swap buffers, so pixel is in pixelBuffer2 and we are drawing in pixelBuffer1
    Uint32 *temp = pixelBuffer1;
    pixelBuffer1 = pixelBuffer2;
    pixelBuffer2 = temp;

    for(int y=0; y<SCREEN_HEIGHT; y++){
        for(int x=0; x<SCREEN_WIDTH; x++){
            /*
             * 0 0 0
             * 0 1 0  --> i-th pixel will take the avg value of neighbors
             * 0 0 0
             */
            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;
            
            for(int row=-1; row<=1; row++){
                for(int col=-1; col<=1; col++){
                    // gaussian kernel
                    int currentX = x + col;
                    int currentY = y + row;
                    // avoid off the edge
                    if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT){
                        // get rgba value
                        Uint32 color = pixelBuffer2[currentY*SCREEN_WIDTH + currentX];
                        // each channel is 1 byte
                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;
                        
                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;
                    }
                }
            }
            // average pixel values for blur
            Uint8 red = redTotal/9;
            Uint8 green = greenTotal/9;
            Uint8 blue = blueTotal/9;
            
            setPixel(x, y, red, green, blue);
        }
    }
}

void Screen::close(){
    delete [] pixelBuffer1;
    delete [] pixelBuffer2;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
