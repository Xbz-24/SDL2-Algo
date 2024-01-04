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
#include <iostream>
#include <boost/log/trivial.hpp>
#include <SDL2/SDL.h>
#include <ctime>
#include <cstdlib>
#include <queue>

 std::array<Maze::Point, 4> Maze::directions = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

/**
 * @brief Constructs a Maze object and initializes its structure.
 *
 * This constructor initializes the maze with given dimensions, then generates the maze.
 *
 * @param rows Number of rows in the maze.
 * @param cols Number of columns in the maze.
 */
Maze::Maze(int rows, int cols) :
        farthestPoint_(),
        farthestPointSet_(),
        path_() ,
        maze_(static_cast<unsigned long>(rows),
    std::vector<Cell>(static_cast<unsigned long>(cols))),
        rows_(rows),
        cols_(cols),
        windowWidth_(0),
        windowHeight_(0),
        wallThickness_(0),
        startPosition_(),
        startPositionSet_(false){
#ifndef ENABLE_LOGGIN
    BOOST_LOG_TRIVIAL(info) << "Creating Maze of size " << rows << "x" << cols;
#endif
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initializeMaze();
    generateMaze();
//    fmt::print("Maze created and generated.\n");
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
    //std::srand(static_cast<unsigned int>(std::time(nullptr)));
    generateMazeRecursive(0, 0);
    for (int r = 0; r < std::min(3, rows_); ++r) {
        for (int c = 0; c < std::min(3, cols_); ++c) {
//            fmt::print("Cell[{},{}]: Top:{} Left:{} Bottom:{} Right:{}\n",
//                       r, c,
//                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].topWall,
//                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].leftWall,
//                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].bottomWall,
//                       maze_[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].rightWall);
        }
    }
}
/**
 * @brief Recursive algorithm to generate   the maze.
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
    //std::vector<std::pair<std::ptrdiff_t , std::ptrdiff_t>> directions = {{1,0}, {-1,0}, {0,1},{0,-1}};

    SodiumRandom randomGen;

    std::shuffle(directions.begin(), directions.end(), randomGen);

    //std::default_random_engine randomGen(std::random_device{}());
    //std::shuffle(directions.begin(), directions.end(), randomGen);

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

int dotX_ = -1;
int dotY_ = -1;

void Maze::render(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 137, 196, 244, 255);
    SDL_RenderClear(renderer);

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
    wallThickness_ = 3;
    int startX = (windowWidth_ - (cellWidth * cols_)) / 2;
    int startY = (windowHeight_ - (cellHeight * rows_)) / 2;
    for (std::size_t r = 0; r < static_cast<std::size_t>(rows_); r++) {
        for (std::size_t c = 0; c < static_cast<std::size_t>(cols_); c++) {
            drawCell(r, c, startX, startY, cellWidth, cellHeight, wallThickness_, renderer);
        }
    }

    if (dotX_ != -1 && dotY_ != -1) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
        SDL_Rect dotRect = {dotX_ - 5, dotY_ - 5, 10, 10}; // Dot size 10x10
        SDL_RenderFillRect(renderer, &dotRect);
    }

    if (farthestPointSet_) {
        int farthestX = startX + farthestPoint_.second * cellWidth + cellWidth / 2;
        int farthestY = startY + farthestPoint_.first * cellHeight + cellHeight / 2;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
        SDL_Rect farthestDotRect = {farthestX - 5, farthestY - 5, 10, 10};
        SDL_RenderFillRect(renderer, &farthestDotRect);
    }

    if (!path_.empty()) {
        SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255); // Purple color
        for (size_t i = 0; i < path_.size() - 1; ++i) {
            int x1 = startX + path_[i].col * cellWidth + cellWidth / 2;
            int y1 = startY + path_[i].row * cellHeight + cellHeight / 2;
            int x2 = startX + path_[i + 1].col * cellWidth + cellWidth / 2;
            int y2 = startY + path_[i + 1].row * cellHeight + cellHeight / 2;
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        }
    }
}

void Maze::setScreenDimensions(int windowWidth, int windowHeight){
    windowWidth_ = windowWidth;
    windowHeight_ = windowHeight;
}


void Maze::handleMouseClick(Sint32 mouseX, Sint32 mouseY, SDL_Window* sdlWindow) {
    int mazeSquareSize = std::min(windowWidth_, windowHeight_) - 100;
    int cellWidth = mazeSquareSize / cols_;
    int cellHeight = mazeSquareSize / rows_;
    int startX = (windowWidth_ - mazeSquareSize) / 2;
    int startY = (windowHeight_ - mazeSquareSize) / 2;

    if (mouseX < startX || mouseY < startY || mouseX > startX + mazeSquareSize || mouseY > startY + mazeSquareSize) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Start Position", "Clicked outside the maze.", sdlWindow);
        return;
    }

    mouseX -= startX;
    mouseY -= startY;

    int col = mouseX / cellWidth;
    int row = mouseY / cellHeight;

    int wallStartX = startX + col * cellWidth;
    int wallStartY = startY + row * cellHeight;
    int wallEndX = wallStartX + cellWidth;
    int wallEndY = wallStartY + cellHeight;

    int buffer = wallThickness_;

    const auto& clickedCell = maze_[static_cast<unsigned long>(row)][static_cast<unsigned long>(col)];
    bool clickedOnWall = (clickedCell.topWall && mouseY < wallStartY + buffer) ||
                         (clickedCell.bottomWall && mouseY > wallEndY - buffer) ||
                         (clickedCell.leftWall && mouseX < wallStartX + buffer) ||
                         (clickedCell.rightWall && mouseX > wallEndX - buffer);

    if (!clickedOnWall) {
        startPosition_ = std::make_pair(row, col);
        startPositionSet_ = true;
        dotX_ = mouseX + startX;
        dotY_ = mouseY + startY;
        std::cout << "Valid click inside the cell.\n";

        Point startPoint(row, col);
        Point endPoint(rows_ - 1, cols_ - 1); // Example endpoint, can be any point
        findShortestPath(startPoint, endPoint);
    } else {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Invalid Start Position", "Clicked on a wall.", sdlWindow);
        std::cout << "Invalid click detected on a wall.\n";
    }
}



void Maze::traceBackPath(const std::map<Point, Point>& predecessor, const Point& start, const Point& end) {
    //std::vector<Point> path;
    path_.clear();
    Point current = end;
    while (current != start) {
        path_.push_back(current);
        current = predecessor.at(current);
    }
    path_.push_back(start);
    std::reverse(path_.begin(), path_.end());
//    for (const auto& point : path_) {
//        std::cout << "(" << point.row << ", " << point.col << ") ";
//    }
    //std::cout << std::endl;
}



void Maze::findShortestPath(Point startPoint, Point endPoint) {
    static_cast<void>(endPoint);
    std::queue<Point> queue;
    std::map<Point, Point> predecessor;
    std::vector<std::vector<bool>> visited(static_cast<unsigned long>(rows_), std::vector<bool>(
            static_cast<unsigned long>(cols_), false));

    queue.push(startPoint);
    visited[static_cast<std::size_t>(startPoint.row)][static_cast<std::size_t>(startPoint.col)] = true;

    int maxDistance = 0;
    Point farthestPoint = startPoint;

    while (!queue.empty()) {
        Point current = queue.front();
        queue.pop();

        int distance = std::abs(current.row - startPoint.row) + std::abs(current.col - startPoint.col);
        if (distance > maxDistance) {
            maxDistance = distance;
            farthestPoint = current;
        }

        for (auto& direction : directions) {
            Point next = current + direction;
            if (isValid(next) && !visited[static_cast<unsigned long>(next.row)][static_cast<unsigned long>(next.col)] && !isWall(current, direction)) {
                visited[static_cast<std::size_t>(next.row)][static_cast<std::size_t>(next.col)] = true;
                predecessor.emplace(next, current);
                queue.push(next);
            }
        }
    }

    farthestPoint_ = std::make_pair(farthestPoint.row, farthestPoint.col); // Convert Point to pair
    farthestPointSet_ = true;
    traceBackPath(predecessor, startPoint, farthestPoint);
}
