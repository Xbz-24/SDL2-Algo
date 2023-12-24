//
// Created by daily on 24-12-23.
//

#ifndef ALGOVISUALIZER_MAZERENDERER_HPP
#define ALGOVISUALIZER_MAZERENDERER_HPP
#include "Maze.hpp"
#include "SDL2/SDL.h"
#include <memory>

class MazeRenderer {
public:
    MazeRenderer(const MazeRenderer&) = delete;
    MazeRenderer& operator=(const MazeRenderer&) = delete;
    MazeRenderer(std::shared_ptr<Maze> maze, SDL_Renderer* renderer);
    void render(int windowWidth, int windowHeight);
private:
    std::shared_ptr<Maze> maze;
    SDL_Renderer* renderer;
    void drawCell(std::size_t row, std::size_t col, int startX, int startY, int cellWidth, int cellHeight, int wallThickness);
};


#endif //ALGOVISUALIZER_MAZERENDERER_HPP
