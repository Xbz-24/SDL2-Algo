//
// Created by daily on 24-12-23.
//
#include "MazeRenderer.hpp"
#include <fmt/core.h>

MazeRenderer::MazeRenderer(std::shared_ptr<Maze> maze_ptr, SDL_Renderer* renderer_ptr):
        maze_(std::move(maze_ptr)),
        sdlRenderer_(renderer_ptr){}

void MazeRenderer::render(int windowWidth, int windowHeight) {
    if(!maze_){
        fmt::print("Maze object is null.\n");
        return;
    }
    fmt::print("Rendering maze_...\n");
    int mazeSquareSize = std::min(windowWidth, windowHeight) - 100;
    int cellWidth = mazeSquareSize / maze_->getCols();
    int cellHeight = mazeSquareSize / maze_->getRows();
    fmt::print("Cell dimensions: {}x{}\n", cellWidth, cellHeight);
    int wallThickness = 4;
    int startX = (windowWidth - (cellWidth * maze_->getCols())) / 2;
    int startY = (windowHeight - (cellHeight * maze_->getRows())) / 2;
    for (std::size_t r = 0; r < static_cast<std::size_t>(maze_->getRows()); r++) {
        for (std::size_t c = 0; c < static_cast<std::size_t>(maze_->getCols()); c++) {
            drawCell(r, c, startX, startY, cellWidth, cellHeight, wallThickness);
        }
    }
}

void MazeRenderer::drawCell(std::size_t row, std::size_t col, int startX, int startY, int cellWidth, int cellHeight, int wallThickness) {
    const auto &cell = maze_->getMaze()[row][col];
    int x = startX + static_cast<int>(col) * cellWidth;
    int y = startY + static_cast<int>(row) * cellHeight;
    SDL_SetRenderDrawColor(sdlRenderer_, 0, 0, 0, 255);

    if (cell.topWall) {
        SDL_Rect topWall = {x, y, cellWidth, wallThickness};
        SDL_RenderFillRect(sdlRenderer_, &topWall);
    }
    if (cell.leftWall) {
        SDL_Rect leftWall = {x, y, wallThickness, cellHeight};
        SDL_RenderFillRect(sdlRenderer_, &leftWall);
    }
    if (cell.bottomWall) {
        SDL_Rect bottomWall = {x, y + cellHeight - wallThickness, cellWidth, wallThickness};
        SDL_RenderFillRect(sdlRenderer_, &bottomWall);
    }
    if (cell.rightWall) {
        SDL_Rect rightWall = {x + cellWidth - wallThickness, y, wallThickness, cellHeight};
        SDL_RenderFillRect(sdlRenderer_, &rightWall);
    }
}