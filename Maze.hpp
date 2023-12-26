/**
 * @file Maze.hpp
 * @brief Class definition for Maze, representing a maze with cells and walls
 * @date Created on 24-12-2023.
 * @author Renato Chavez
 */
#ifndef ALGOVISUALIZER_MAZE_HPP
#define ALGOVISUALIZER_MAZE_HPP
/**
 * Standard library vector for dynamic array management.
 */
#include <vector>
/**
 * Standard library cstdlib for general purpose functions.
 */
#include <cstdlib>
/**
 * @brief Represents a maze with cells and walls.
 *
 * The Maze class stores a maze grid where each cell can have walls on four sides.
 * It provides functionality to generate and access the maze structure.
 */
#include "IRenderable.hpp"
class Maze : public IRenderable{
public:
    /**
     * @brief Represents a single cell in the maze.
     *
     * Each cell has four walls and a visited flag, which can be used for maze generation algorithms.
     */
    struct Cell {
        bool visited;
        bool topWall;
        bool leftWall;
        bool bottomWall;
        bool rightWall;
    };
    /**
     * @brief Constructs a Maze object with specified dimensions.
     * @param rows Number of rows in the maze.
     * @param cols Number of columns in the maze.
     */
    Maze(int rows, int cols);
    /**
     * @brief Generates the maze structure.
     *
     * This method uses a maze generation algorithm to create a maze with one possible path.
     */
    void generateMaze();

    [[nodiscard]] int getRows() const { return rows_; }
    [[nodiscard]] int getCols() const { return cols_; }
    [[nodiscard]] const std::vector<std::vector<Cell>>& getMaze() const;
    void update() override{}
    void render(SDL_Renderer* renderer) override;
    void setScreenDimensions(int screenWidth, int screenHeight);
private:
    /**
     * @brief Initializes the maze grid.
     *
     * Sets up the grid with specified dimensions and initializes cells.
     */
    void initializeMaze();
    /**
     * @brief Recursive function to generate the maze.
     *
     * @param r Row index for the current cell.
     * @param c Column index for the current cell.
     */
    void generateMazeRecursive(std::size_t r, std::size_t c);

    /**
     * @brief 2D grid representing the maze.
     * A vector of vectorof cells, where each cell represents a position in the maze.
     */
    std::vector<std::vector<Cell>> maze_;
    /**
     * @brief Number of rows in the maze.
     */
    int rows_;
    /**
     * @brief Number of columns in the maze.
     */
    int cols_;
    int windowWidth_;
    int windowHeight_;

    void drawCell(std::size_t row, std::size_t col, int startX, int startY, int cellWidth, int cellHeight, int wallThickness, SDL_Renderer* sdlRenderer);
};
#endif //ALGOVISUALIZER_MAZE_HPP