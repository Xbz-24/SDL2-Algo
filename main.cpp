#include <SDL2/SDL.h>
#include "Visualizer.hpp"
#include "Maze.hpp"
#include "CustomCursor.h"

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL could not initialize: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto mazeVisualizer = std::make_unique<Visualizer>("Maze Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 900, true);
    auto maze = std::make_shared<Maze>(20,20);
    maze->setScreenDimensions(800, 900);
    mazeVisualizer->setMaze(maze);
    mazeVisualizer->addRenderable(maze);
    std::cout << "Created Maze Window with ID:"<< SDL_GetWindowID(mazeVisualizer->getWindow()) << '\n';

    auto squareVisualizer = std::make_unique<Visualizer>("Square Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 900, true);
    auto square1 = std::make_shared<Square>(100, 100, 20, SDL_Color{255,0,0,255});
    auto square2 = std::make_shared<Square>(300, 300, 40, SDL_Color{0,255,0,255});
    square1->setScreenDimensions(800, 900);
    square2->setScreenDimensions(800, 900);
    squareVisualizer->addRenderable(square1);
    squareVisualizer->addRenderable(square2);
    std::cout << "Created Square Window with ID:"<< SDL_GetWindowID(squareVisualizer->getWindow()) << '\n';

    while (mazeVisualizer->running() && squareVisualizer->running()) {
        mazeVisualizer->handleEvents();
        squareVisualizer->handleEvents();

        mazeVisualizer->update();
        mazeVisualizer->render();

        squareVisualizer->update();
        squareVisualizer->render();
    }

    mazeVisualizer->clean();
    squareVisualizer->clean();
    SDL_Quit();
}
