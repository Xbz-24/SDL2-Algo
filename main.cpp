#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <fmt/core.h>
#include <SDL.h>
#include "MazeVisualizer.hpp"
#include "Maze.hpp"
//#include "maze_visualizer.hpp"

int main(){
    auto *visualizer = new MazeVisualizer();
    Maze maze(10,10);
    visualizer->setMaze(&maze);
    visualizer->init("Maze-MazeVisualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, true);
    while(visualizer->running()){
        visualizer->handleEvents();
        visualizer->update();
        visualizer->render();
    }
    visualizer->clean();
    delete visualizer;
}

