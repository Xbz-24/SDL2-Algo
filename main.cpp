#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <fmt/core.h>
#include <SDL.h>
#include "Visualizer.hpp"
#include "Maze.hpp"

int main()
{
    auto visualizer = std::make_unique<Visualizer>("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true);
    auto maze = std::make_shared<Maze>(60,60);
    visualizer->setMaze(maze);
    //visualizer->init("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true);
    while(visualizer->running())
    {
        visualizer->handleEvents();
        visualizer->update();
        visualizer->render();
    }
    visualizer->clean();
}

