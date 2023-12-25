/**
 * @file FPSCounter.hpp
 * @brief Definition of the FPSCounter class for frame rate calculation and rendering.
 * @date Created on 24-12-23
 * @author Renato Chavez
 */
#ifndef ALGOVISUALIZER_FPSCOUNTER_HPP
#define ALGOVISUALIZER_FPSCOUNTER_HPP
/**
 * @brief Includes SDL2 main header for rendering functionalities.
 */
#include "SDL2/SDL.h"
/**
 * @brief Includes SDL2 extension for TrueType font rendering.
 */
#include "SDL2/SDL_ttf.h"
/**
 * @brief
 */
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
    /**
     * @brief SDL_Renderer used for rendering the FPS text.
     */
    SDL_Renderer* renderer;
    /**
     * @brief TTF_Font used for displaying the FPS text.
     */
    TTF_Font* font;
    /**
     * @brief Timestamp of the last frame update.
     */
    Uint32 lastTime;
    /**
     * @brief Count of frames rendered since the last update.
     */
    int frameCount;
    /**
     * @brief Calculated frames per second.
     */
    float fps;
    /**
     * @brief Color used for rendering the FPS text.
     */
    SDL_Color textColor;
};
#endif //ALGOVISUALIZER_FPSCOUNTER_HPP