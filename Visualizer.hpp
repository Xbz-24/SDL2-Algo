//
// Created by daily on 23-12-23.
//

#ifndef ALGOVISUALIZER_VISUALIZER_HPP
#define ALGOVISUALIZER_VISUALIZER_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include "Maze.hpp"

class Visualizer {
public:
    Visualizer(const Visualizer&) = delete;
    Visualizer& operator=(const Visualizer&) = delete;
    Visualizer();
    ~Visualizer();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    void setMaze(Maze* m);
    [[nodiscard]] bool running() const
    {
        return isRunning;
    }
    void renderMaze();
private:
    Maze* maze = nullptr;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int windowWidth;
    int windowHeight;
};


#endif //ALGOVISUALIZER_VISUALIZER_HPP
