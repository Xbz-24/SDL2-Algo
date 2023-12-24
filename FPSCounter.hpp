//
// Created by daily on 24-12-23.
//

#ifndef ALGOVISUALIZER_FPSCOUNTER_HPP
#define ALGOVISUALIZER_FPSCOUNTER_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class FPSCounter
{
public:
    FPSCounter(SDL_Renderer* renderer, TTF_Font* font);
    void update();
    void render();
private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    Uint32 lastTime;
    int frameCount;
    float fps;
    SDL_Color textColor;
};


#endif //ALGOVISUALIZER_FPSCOUNTER_HPP
