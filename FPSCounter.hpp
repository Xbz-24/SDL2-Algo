//
// Created by daily on 24-12-23.
//

#ifndef ALGOVISUALIZER_FPSCOUNTER_HPP
#define ALGOVISUALIZER_FPSCOUNTER_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

/**
 * @brief A class to count and display frames per second (FPS).
 *
 * The FPSCounter class is responsible for calculating the frames per second and rendering this information on screen.
 * It uses SDL and SDL_ttf for rendering the FPS count.
 */

class FPSCounter{
public:
    /**
     * @brief Constructor for the FPSCounter.
     *
     *  Initializes the FPS counter with the SDL_Renderer and TTF_Font to be used for rendering the text.
     *
     * @param renderer SDL_Renderer used for rendering the FPS text.
     * @param font TTF_Font used to display the FPS text.
     */
    FPSCounter(SDL_Renderer* renderer, TTF_Font* font);
    /**
     * @brief Updates the FPS counter.
     *
     * Calculates the current frames per second based on the number of frames rendered.
     */
    void update();
    /**
     * @brief Renders the FPS count to the screen.
     *
     * Displays the current FPS on the screen using the provided SDL_Renderer and TTF_Font.
     */
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