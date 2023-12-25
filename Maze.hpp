//
// Created by daily on 24-12-23.
//

#ifndef ALGOVISUALIZER_MAZE_HPP
#define ALGOVISUALIZER_MAZE_HPP
#include <vector>
#include <cstdlib>

class Maze {
public:
    struct Cell {
        bool visited;
        bool topWall;
        bool leftWall;
        bool bottomWall;
        bool rightWall;
    };

    Maze(int rows, int cols);
    void generateMaze();
    [[nodiscard]] int getRows() const { return rows_; }
    [[nodiscard]] int getCols() const { return cols_; }
    [[nodiscard]] const std::vector<std::vector<Cell>>& getMaze() const;

private:
    std::vector<std::vector<Cell>> maze_;
    int rows_;
    int cols_;
    void initializeMaze();
    void generateMazeRecursive(std::size_t r, std::size_t c);
};
#endif //ALGOVISUALIZER_MAZE_HPP
