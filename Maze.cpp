/**
 * @file Maze.cpp
 * @brief
 * @date Created on 24-12-23
 * @author Renato Chavez
 */
#include "Maze.hpp"
#include <algorithm>
#include <limits>
#include <utility>
#include <fmt/core.h>

/**
 * @brief Constructs a Maze object and initializes its structure.
 *
 * This constructor initializes the maze with given dimensions, then generates the maze.
 *
 * @param rows Number of rows in the maze.
 * @param cols Number of columns in the maze.
 */
Maze::Maze(int rows, int cols) : maze_(static_cast<unsigned long>(rows), std::vector<Cell>(
        static_cast<unsigned long>(cols))), rows_(rows) , cols_(cols) {
    fmt::print("Creating Maze of size {}x{}\n", rows, cols);
    initializeMaze();
    generateMaze();
    fmt::print("Maze created and generated.\n");
}
/**
 * @brief Initializes the maze grid with default cell values.
 *
 * Sets up each cell in the maze grid with default wall values and visited status.
 */
void Maze::initializeMaze() {
    maze_.resize(static_cast<std::size_t>(rows_), std::vector<Cell>(static_cast<std::size_t>(cols_)));
    for (auto& row : maze_) {
        for (auto& cell : row) {
            cell.visited = false;
            cell.topWall = true;
            cell.leftWall = true;
            cell.bottomWall = true;
            cell.rightWall = true;
        }
    }
}
/**
 * @brief Public interface to generate the maze structure.
 *
 * Initiates the recursive maze generation algorithm.
 */
void Maze::generateMaze() {
    generateMazeRecursive(0, 0);
    for (int r = 0; r < std::min(3, rows_); ++r) {
        for (int c = 0; c < std::min(3, cols_); ++c) {
            fmt::print("Cell[{},{}]: Top:{} Left:{} Bottom:{} Right:{}\n",
                       r, c,
                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].topWall,
                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].leftWall,
                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].bottomWall,
                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].rightWall);
        }
    }
}
/**
 * @brief Recursive algorithm to generate the maze.
 *
 * Randomly selects a direction and carves a path in the maze grid recursively.
 *
 * @param r Row index for the current cell.
 * @param c Column index for the current cell.
 */
void Maze::generateMazeRecursive(std::size_t r, std::size_t c) {
    fmt::print("Generating maze_ at cell [{}, {}]\n", r, c);
    std::vector<std::pair<std::ptrdiff_t , std::ptrdiff_t>> directions = {{1,0}, {-1,0}, {0,1},{0,-1}};
    std::random_shuffle(directions.begin(), directions.end());
    maze_[r][c].visited = true;

    for(auto [dr, dc] : directions){
        if (dr < 0){
            // Underflow check
            if (static_cast<std::size_t>(-dr) > r)
                continue;
        }
        else{
            // Overflow check
            if (dr >= 0 && r > std::numeric_limits<std::size_t>::max() - static_cast<std::size_t>(dr))
                continue;
        }

        if (dc < 0){
            // Underflow check
            if (static_cast<std::size_t>(-dc) > c)
                continue;
        }
        else{
            // Overflow check
            if (dc >= 0 && c > std::numeric_limits<std::size_t>::max() - static_cast<std::size_t>(dc))
                continue;
        }

        std::size_t newR = r + static_cast<std::size_t>(dr);
        std::size_t newC = c + static_cast<std::size_t>(dc);

        if(newR < static_cast<std::size_t>(rows_) && newC < static_cast<std::size_t>(cols_) && !maze_[newR][newC].visited){
            if(dr == -1){
                maze_[r][c].topWall = false;
                maze_[newR][newC].bottomWall = false;
            }
            if(dr == 1){
                maze_[r][c].bottomWall = false;
                maze_[newR][newC].topWall = false;
            }
            if(dc == -1){
                maze_[r][c].leftWall = false;
                maze_[newR][newC].rightWall = false;
            }
            if(dc == 1){
                maze_[r][c].rightWall = false;
                maze_[newR][newC].leftWall = false;
            }
            generateMazeRecursive(newR, newC);
        }
    }
}
/**
 * @brief Returns a constant reference to the maze grid.
 *
 * @return Constant reference to the maze's 2D cell grid.
 */
const std::vector<std::vector<Maze::Cell>>& Maze::getMaze() const {
    return maze_;
}