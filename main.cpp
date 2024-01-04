#include <SDL2/SDL.h>
#include "Visualizer.hpp"
#include "Maze.hpp"
#include "CustomCursor.h"
#include "Tetris.h"

int main() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL could not initialize: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto mazeVisualizer = std::make_unique<Visualizer>("Maze Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 750, 750, true);
    auto maze = std::make_shared<Maze>(20,20);
    maze->setScreenDimensions(750, 750);
    mazeVisualizer->setMaze(maze);
    mazeVisualizer->addRenderable(maze);
    std::cout << "Created Maze Window with ID:"<< SDL_GetWindowID(mazeVisualizer->getWindow()) << '\n';

    auto tetrisVisualizer = std::make_unique<Visualizer>("Tetris Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 700, true);
    auto tetrisGame = std::make_shared<Tetris>();
    tetrisGame->setScreenDimensions(400, 700);
    tetrisVisualizer->addRenderable(tetrisGame);
    std::cout << "Created Tetris Window with ID: " << SDL_GetWindowID(tetrisVisualizer->getWindow()) << '\n';

    auto squareVisualizer = std::make_unique<Visualizer>("Square Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 500, true);
    auto square1 = std::make_shared<Square>(100, 100, 20, SDL_Color{255, 0, 0, 255});        // Red
    auto square2 = std::make_shared<Square>(300, 300, 40, SDL_Color{0, 255, 0, 255});      // Green
    auto square3 = std::make_shared<Square>(200, 200, 30, SDL_Color{0, 0, 255, 255});      // Blue
    auto square4 = std::make_shared<Square>(50, 400, 15, SDL_Color{255, 255, 0, 255});     // Yellow
    auto square5 = std::make_shared<Square>(350, 150, 25, SDL_Color{255, 0, 255, 255});    // Magenta
    auto square6 = std::make_shared<Square>(250, 50, 35, SDL_Color{0, 255, 255, 255});     // Cyan
    auto square7 = std::make_shared<Square>(50, 50, 15, SDL_Color{255, 128, 0, 255});     // Orange
    auto square8 = std::make_shared<Square>(150, 350, 25, SDL_Color{128, 0, 128, 255});   // Purple
    auto square9 = std::make_shared<Square>(350, 350, 45, SDL_Color{128, 128, 0, 255});   // Olive
    auto square10 = std::make_shared<Square>(125, 250, 20, SDL_Color{0, 128, 128, 255});  // Teal
    auto square11 = std::make_shared<Square>(75, 75, 18, SDL_Color{0, 255, 128, 255});    // Turquoise
    auto square12 = std::make_shared<Square>(175, 175, 22, SDL_Color{128, 0, 0, 255});    // Maroon
    auto square13 = std::make_shared<Square>(275, 275, 28, SDL_Color{0, 128, 0, 255});    // Lime Green
    auto square14 = std::make_shared<Square>(375, 375, 33, SDL_Color{128, 0, 255, 255});  // Lavender
    auto square15 = std::make_shared<Square>(400, 200, 25, SDL_Color{255, 165, 0, 255});  // Orange-Red

    square1->setScreenDimensions(400, 500);
    square2->setScreenDimensions(400, 500);
    square3->setScreenDimensions(400, 500);
    square4->setScreenDimensions(400, 500);
    square5->setScreenDimensions(400, 500);
    square6->setScreenDimensions(400, 500);
    square7->setScreenDimensions(400, 500);
    square8->setScreenDimensions(400, 500);
    square9->setScreenDimensions(400, 500);
    square10->setScreenDimensions(400, 500);
    square11->setScreenDimensions(400, 500);
    square12->setScreenDimensions(400, 500);
    square13->setScreenDimensions(400, 500);
    square14->setScreenDimensions(400, 500);
    square15->setScreenDimensions(400, 500);

    squareVisualizer->addRenderable(square1);
    squareVisualizer->addRenderable(square2);
    squareVisualizer->addRenderable(square3);
    squareVisualizer->addRenderable(square4);
    squareVisualizer->addRenderable(square5);
    squareVisualizer->addRenderable(square6);
    squareVisualizer->addRenderable(square7);
    squareVisualizer->addRenderable(square8);
    squareVisualizer->addRenderable(square9);
    squareVisualizer->addRenderable(square10);
    squareVisualizer->addRenderable(square11);
    squareVisualizer->addRenderable(square12);
    squareVisualizer->addRenderable(square13);
    squareVisualizer->addRenderable(square14);
    squareVisualizer->addRenderable(square15);

    std::cout << "Created Square Window with ID:"<< SDL_GetWindowID(squareVisualizer->getWindow()) << '\n';

    while (mazeVisualizer->running() && squareVisualizer->running() && tetrisVisualizer->running()) {
        mazeVisualizer->handleEvents();
        squareVisualizer->handleEvents();
        tetrisVisualizer->handleEvents();

        mazeVisualizer->update();
        squareVisualizer->update();
        tetrisVisualizer->update();

        mazeVisualizer->render();
        tetrisVisualizer->render();
        squareVisualizer->render();
    }
    mazeVisualizer->clean();
    squareVisualizer->clean();
    tetrisVisualizer->clean();
    SDL_Quit();
}
