//
// Created by daily on 23-12-23.
//

#include "Visualizer.hpp"
#include <fmt/core.h>

Visualizer::Visualizer() : maze(nullptr) , isRunning(false), window(nullptr), renderer(nullptr), windowWidth(0), windowHeight(0) {

}

Visualizer::~Visualizer() {
}

void Visualizer::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    windowHeight = height;
    windowWidth = width;
    Uint32 flags = fullscreen ? SDL_WINDOW_MAXIMIZED: 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        fmt::println("Subsystems Initialized! ...");
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            fmt::println("Window created!");
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                fmt::println("Renderer created!");
                isRunning = true;
            } else {
                fmt::println("Failed to create renderer!");
                isRunning = false;
            }
        } else {
            fmt::println("Failed to create window!");
            isRunning = false;
        }
    }
    else{
        isRunning = false;
    }
}
void Visualizer::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}
void Visualizer::update() {

}
void Visualizer::render() {
    fmt::print("Rendering frame...\n");
    SDL_RenderClear(renderer);
    renderMaze();
    SDL_RenderPresent(renderer);
    fmt::print("Frame rendered.\n");
}
void Visualizer::clean() {
    SDL_DestroyWindow(window);

}
void Visualizer::renderMaze() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_Rect rect = {5, 5, 20, 20};
    SDL_RenderFillRect(renderer, &rect);
//    if(maze){
//        fmt::print("Rendering maze...\n");
//        const auto& cells = maze->getMaze();
//        int cellWidth = windowWidth / maze->getCols();
//        int cellHeight = windowHeight / maze->getRows();
//        fmt::print("Cell dimensions: {}x{}\n", cellWidth, cellHeight);
//
//        for (std::size_t r = 0; r < cells.size(); ++r) {
//            for (std::size_t c = 0; c < cells[r].size(); ++c) {
//                const auto& cell = cells[r][c];
//                int x = static_cast<int>(c) * cellWidth;
//                int y = static_cast<int>(r) * cellHeight;
//
//                // Set the draw color for the walls, e.g., black
//                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//
//                // Draw the walls as needed
//                if (cell.topWall) {
//                    SDL_RenderDrawLine(renderer, x, y, x + cellWidth, y);
//                }
//                if (cell.leftWall) {
//                    SDL_RenderDrawLine(renderer, x, y, x, y + cellHeight);
//                }
//                if (cell.bottomWall) {
//                    SDL_RenderDrawLine(renderer, x, y + cellHeight, x + cellWidth, y + cellHeight);
//                }
//                if (cell.rightWall) {
//                    SDL_RenderDrawLine(renderer, x + cellWidth, y, x + cellWidth, y + cellHeight);
//                }
//            }
//        }
//    }else{
//        fmt::print("Maze object is null.\n");
//    }
}

void Visualizer::setMaze(Maze *m) {
    maze = m;
}
