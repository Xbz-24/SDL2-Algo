//
// Created by daily on 24-12-23.
//
#include "MazeRenderer.hpp"
#include <fmt/core.h>

MazeRenderer::MazeRenderer(std::shared_ptr<Maze> maze_ptr, SDL_Renderer* renderer_ptr):
maze(std::move(maze_ptr)),
renderer(renderer_ptr){}

void MazeRenderer::render(int windowWidth, int windowHeight) {
    if(!maze){
        fmt::print("Maze object is null.\n");
        return;
    }
    fmt::print("Rendering maze...\n");
    int mazeSquareSize = std::min(windowWidth, windowHeight) - 100;
    int cellWidth = mazeSquareSize/ maze->getCols();
    int cellHeight = mazeSquareSize / maze->getRows();
    fmt::print("Cell dimensions: {}x{}\n", cellWidth, cellHeight);
    int wallThickness = 4;
    int startX = (windowWidth - (cellWidth * maze->getCols())) / 2;
    int startY = (windowHeight - (cellHeight * maze->getRows())) / 2;
    for (std::size_t r = 0; r < static_cast<std::size_t>(maze->getRows()); r++) {
        for (std::size_t c = 0; c < static_cast<std::size_t>(maze->getCols()); c++) {
            drawCell(r, c, startX, startY, cellWidth, cellHeight, wallThickness);
        }
    }
}

void MazeRenderer::drawCell(std::size_t row, std::size_t col, int startX, int startY, int cellWidth, int cellHeight, int wallThickness) {
    const auto &cell = maze->getMaze()[row][col];
    int x = startX + static_cast<int>(col) * cellWidth;
    int y = startY + static_cast<int>(row) * cellHeight;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    if (cell.topWall) {
        SDL_Rect topWall = {x, y, cellWidth, wallThickness};
        SDL_RenderFillRect(renderer, &topWall);
    }
    if (cell.leftWall) {
        SDL_Rect leftWall = {x, y, wallThickness, cellHeight};
        SDL_RenderFillRect(renderer, &leftWall);
    }
    if (cell.bottomWall) {
        SDL_Rect bottomWall = {x, y + cellHeight - wallThickness, cellWidth, wallThickness};
        SDL_RenderFillRect(renderer, &bottomWall);
    }
    if (cell.rightWall) {
        SDL_Rect rightWall = {x + cellWidth - wallThickness, y, wallThickness, cellHeight};
        SDL_RenderFillRect(renderer, &rightWall);
    }
}