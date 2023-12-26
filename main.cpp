#include <SDL2/SDL.h>
#include "Visualizer.hpp"
#include "Maze.hpp"

int main(){
    auto visualizer = std::make_unique<Visualizer>("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true);

    auto maze = std::make_shared<Maze>(60,60);
    maze->setScreenDimensions(1920, 1080);
    visualizer->addRenderable(maze);

    auto square1 = std::make_shared<Square>(100, 100, 20, SDL_Color{255,0,0,255});
    square1->setScreenDimensions(1920, 1080);
//    visualizer->addRenderable(square1);

    auto square2 = std::make_shared<Square>(300, 300, 40, SDL_Color{0,255,0,255});
    square2->setScreenDimensions(1920, 1080);
//    visualizer->addRenderable(square2);

    while(visualizer->running()){
        visualizer->handleEvents();
        visualizer->update();
        visualizer->render();
    }
    visualizer->clean();
}