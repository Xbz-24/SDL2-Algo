//
// Created by daily on 23-12-23.
//

#ifndef ALGOVISUALIZER_VISUALIZER_HPP
#define ALGOVISUALIZER_VISUALIZER_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include "Maze.hpp"
#include "FPSCounter.hpp"
#include "MazeRenderer.hpp"
#include <memory>

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
    void setMaze(std::shared_ptr<Maze> m);
    [[nodiscard]] bool running() const;
    void initSDL();
    void createWindow(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void createRenderer();
    void initTTF();
    void initializeSDLComponents(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
private:
    std::shared_ptr<Maze> maze;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int windowWidth;
    int windowHeight;
    TTF_Font *fpsFont;
    FPSCounter fpsCounter;
    std::unique_ptr<MazeRenderer> mazeRenderer;
};
#endif //ALGOVISUALIZER_VISUALIZER_HPP
