//
// Created by daily on 24-12-23.
//

#include "FPSCounter.hpp"
#include <fmt/core.h>

FPSCounter::FPSCounter(SDL_Renderer *rendererArg, TTF_Font *fontArg)
: renderer(rendererArg), font(fontArg), lastTime(0), frameCount(0), fps(0.0f), textColor({255,255,255,255}){}

void FPSCounter::update() {
    Uint32 currentTime = SDL_GetTicks();
    frameCount++;
    if(currentTime - lastTime > 1000){
        fps = static_cast<float>(frameCount) / ((static_cast<float>(currentTime - lastTime)) / 1000.0f);
        frameCount = 0;
        lastTime = currentTime;
    }
}
void FPSCounter::render(){
    std::string fpsText = fmt::format("FPS: {:.2f}", fps);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, fpsText.c_str(), textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {10, 10 , textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}