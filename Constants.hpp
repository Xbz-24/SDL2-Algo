//
// Created by daily on 24-12-23.
//
#ifndef ALGOVISUALIZER_CONSTANTS_HPP
#define ALGOVISUALIZER_CONSTANTS_HPP
#include <SDL.h>

namespace Constants{
    constexpr Uint32 SDL_INIT_FLAGS = SDL_INIT_EVERYTHING;
    constexpr int DEFAULT_WINDOW_WIDTH = 800;
    constexpr int DEFAULT_WINDOW_HEIGHT = 600;
    constexpr int DEFAULT_WINDOW_POS_X = SDL_WINDOWPOS_CENTERED;
    constexpr int DEFAULT_WINDOW_POS_Y = SDL_WINDOWPOS_CENTERED;
    constexpr bool DEFAULT_FULLSCREEN = false;
    constexpr Uint8 RENDER_COLOR_R = 255;
    constexpr Uint8 RENDER_COLOR_G = 255;
    constexpr Uint8 RENDER_COLOR_B = 255;
    constexpr Uint8 RENDER_COLOR_A = 255;
    const char* const FONT_PATH = "../fonts/HackNerdFont-Regular.ttf";
    constexpr int FONT_SIZE = 24;
    const char* const INITIALIZING_VISUALIZER = "Initializing Visualizer with title: ";
    const char* const CLEANING_UP_VISUALIZER = "Cleaning up Visualizer resources.";
    const char* const SDL_INIT_ERROR = "SDL could not initialize: ";
    const char* const WINDOW_CREATION_ERROR = "Failed to create sdlWindow_: ";
    const char* const RENDERER_CREATION_ERROR = "Failed to create sdlRenderer_: ";
    const char* const TTF_INIT_ERROR = "SDL_ttf could not initialize: ";
    const char* const FONT_LOAD_ERROR = "Failed to load font: ";
};
#endif //ALGOVISUALIZER_CONSTANTS_HPP