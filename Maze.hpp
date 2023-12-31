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
#include <cryptopp/osrng.h>
#include <sodium.h>
#include <array>
/**
 * @brief Represents a maze with cells and walls.
 *
 * The Maze class stores a maze grid where each cell can have walls on four sides.
 * It provides functionality to generate and access the maze structure.
 */
#include "IRenderable.hpp"
#include <random>
class Maze : public IRenderable{
public:
    /**
     * @brief Represents a single cell in the maze.
     *
     * Each cell has four walls and a visited flag, which can be used for maze generation algorithms.
     */

    std::pair<int, int> farthestPoint_;
    bool farthestPointSet_;

    struct Point {
        int row;
        int col;
        Point(int x , int y) : row(x), col(y) {}
        bool operator ==(const Point& other) const{
            return row == other.row && col == other.col;
        }
        Point operator+(const Point& other) const {
            return {row + other.row, col + other.col};
        }
        bool operator<(const Point& other) const {
            return std::tie(row, col) < std::tie(other.row, other.col);
        }
    };
    std::vector<Point> path_;

    static  std::array<Point, 4> directions;
    struct Cell {
        bool visited;
        bool topWall;
        bool leftWall;
        bool bottomWall;
        bool rightWall;
        bool isBlocked(const Point& direction) const {
            if(direction.row == -1 && topWall) return true;
            if(direction.row == 1 && bottomWall) return true;
            if(direction.col == -1 && leftWall) return true;
            if(direction.col == 1 && rightWall) return true;
            return false;
        }
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
    void handleMouseClick(Sint32 mouseX, Sint32 mouseY, SDL_Window* sdlWindow);
    [[nodiscard]] std::pair<int, int> getStartPosition() const {
        return startPosition_;
    }
    void findShortestPath(Point startPoint, Point endPoint);

    bool isValid(const Point& p) const {
        return p.row >= 0 && p.row < rows_ && p.col >= 0 && p.col < cols_;
    }
    bool isWall(const Point& current, const Point& direction) const {

        return maze_[static_cast<unsigned long>(current.row)][static_cast<unsigned long>(current.col)].isBlocked(direction);
    }
    void traceBackPath(const std::map<Point, Point>& predecessor, const Point& start, const Point& end);

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
    int wallThickness_;

    std::pair<int, int> startPosition_;
    bool startPositionSet_;

    void drawCell(std::size_t row, std::size_t col, int startX, int startY, int cellWidth, int cellHeight, int wallThickness, SDL_Renderer* sdlRenderer);

    class SodiumRandom {
    public:
        using result_type = uint32_t;

        static constexpr result_type min() { return 0; }
        static constexpr result_type max() { return UINT32_MAX; }

        result_type operator()() {
            return randombytes_random();
        }
    };

};
#endif //ALGOVISUALIZER_MAZE_HPP