/**
 * @file MazeRenderer.hpp
 * @brief
 * @date Created on 24-12-23.
 * @author Renato Chavez
 */
#ifndef ALGOVISUALIZER_MAZERENDERER_HPP
#define ALGOVISUALIZER_MAZERENDERER_HPP
#include "Maze.hpp"
#include "SDL2/SDL.h"
#include <memory>
/**
 * @brief Renders a Maze object using SDL.
 *
 * The MazeRenderer class is responsible for visualizing a Maze object. It uses SDL for rendering
 * the maze's cells, walls and other featuresto an SDL window. This class cannot be copied or assigned.
 */
class MazeRenderer {
public:
    MazeRenderer(const MazeRenderer&) = delete;
    MazeRenderer& operator=(const MazeRenderer&) = delete;
   /**
    * @brief Constructs a MazeRenderer.
    *
    * Initializes the MazeRenderer with a shared pointer to a Maze object and a SDL_Renderer.
    *
    * @param maze Shared pointer to the Maze object to be rendered.
    * @param renderer SDL_Renderer to be used for rendering the maze.
    */
    MazeRenderer(std::shared_ptr<Maze> maze, SDL_Renderer* renderer);
    /**
     * @brief Renders the maze to the SDL window.
     *
     * Draws the maze's cells and walls onto the SDL window based on the maze's current state.
     *
     * @param windowWidth Width of the window in which the maze is being rendered.
     * @param windowHeight Height of the window in which the maze is being rendered.
     */
    void render(int windowWidth, int windowHeight);
private:
    /**
     * @brief Draws an individual cell of the maze.
     *
     * Draws a single cell of the maze, including its walls, based on the cell's state.
     *
     * @param row Row index of the cell in the maze.
     * @param col Column index of the cell in the maze.
     * @param startX startX X-coordinate of the start position for rendering.
     * @param startY startY Y-coordinate of the start position for rendering.
     * @param cellWidth Width of the cell.
     * @param cellHeight Height of the cell.
     * @param wallThickness Thickness of the walls of the cell.
     */
    void drawCell(std::size_t row, std::size_t col, int startX, int startY, int cellWidth, int cellHeight, int wallThickness);
    std::shared_ptr<Maze> maze_;
    SDL_Renderer* sdlRenderer_;
};
#endif //ALGOVISUALIZER_MAZERENDERER_HPP
