//
// Created by daily on 23-12-23.
//

#ifndef ALGOVISUALIZER_MAZEVISUALIZER_HPP
#define ALGOVISUALIZER_MAZEVISUALIZER_HPP
#include "SDL2/SDL.h"
#include <iostream>
#include "Maze.hpp"

class MazeVisualizer {
public:
    MazeVisualizer(const MazeVisualizer&) = delete;
    MazeVisualizer& operator=(const MazeVisualizer&) = delete;
    MazeVisualizer();
    ~MazeVisualizer();
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
    int windowWidth = 800;
    int windowHeight = 600;
};


#endif //ALGOVISUALIZER_MAZEVISUALIZER_HPP
