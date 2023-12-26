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
#include <boost/log/trivial.hpp>

/**
 * @brief Constructs a Maze object and initializes its structure.
 *
 * This constructor initializes the maze with given dimensions, then generates the maze.
 *
 * @param rows Number of rows in the maze.
 * @param cols Number of columns in the maze.
 */
Maze::Maze(int rows, int cols) : maze_(static_cast<unsigned long>(rows), std::vector<Cell>(
        static_cast<unsigned long>(cols))), rows_(rows) , cols_(cols), windowWidth_(0), windowHeight_(0) {
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(info) << "Creating Maze of size " << rows << "x" << cols;
#endif
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
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(debug) << "Initializing Maze grid.";
#endif
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
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(info) << "Generating Maze.";
#endif
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
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(trace) << "Generating maze at cell [" << r << ", " << c << "]";
#endif
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

void Maze::drawCell(std::size_t row, std::size_t col, int startX, int startY, int cellWidth, int cellHeight, int wallThickness, SDL_Renderer* renderer) {
    const auto &cell = maze_[row][col];
    int x = startX + static_cast<int>(col) * cellWidth;
    int y = startY + static_cast<int>(row) * cellHeight;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    if (cell.topWall) {
        SDL_Rect topWall = {x, y, cellWidth, wallThickness};
        SDL_RenderFillRect(renderer, &topWall);
    }
    if (cell.leftWall) {
        SDL_Rect leftWall = {x, y, wallThickness, cellHeight};
        SDL_RenderFillRect(renderer, &leftWall);
    }
    if (cell.bottomWall) {
        SDL_Rect bottomWall = {x, y + cellHeight - wallThickness, cellWidth, wallThickness};
        SDL_RenderFillRect(renderer, &bottomWall);
    }
    if (cell.rightWall) {
        SDL_Rect rightWall = {x + cellWidth - wallThickness, y, wallThickness, cellHeight};
        SDL_RenderFillRect(renderer, &rightWall);
    }
}

void Maze::render(SDL_Renderer* renderer){
    if(!maze_.size()){
#ifndef ENABLE_LOGGING
        BOOST_LOG_TRIVIAL(warning) << "Maze object is null. Rendering aborted.";
#endif
        return;
    }
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(info) << "Rendering maze...";
#endif
    int mazeSquareSize = std::min(windowWidth_, windowHeight_) - 100;
    int cellWidth = mazeSquareSize / cols_;
    int cellHeight = mazeSquareSize / rows_;
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(debug) << "Cell dimensions: " << cellWidth << "x" << cellHeight;
#endif
    int wallThickness = 4;
    int startX = (windowWidth_ - (cellWidth * cols_)) / 2;
    int startY = (windowHeight_ - (cellHeight * rows_)) / 2;
    for (std::size_t r = 0; r < static_cast<std::size_t>(rows_); r++) {
        for (std::size_t c = 0; c < static_cast<std::size_t>(cols_); c++) {
            drawCell(r, c, startX, startY, cellWidth, cellHeight, wallThickness, renderer);
        }
    }
}

void Maze::setScreenDimensions(int windowWidth, int windowHeight){
    windowWidth_ = windowWidth;
    windowHeight_ = windowHeight;
}
