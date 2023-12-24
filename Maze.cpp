//
// Created by daily on 24-12-23.
//

#include "Maze.hpp"
#include <algorithm>
#include <limits>
#include <utility>
#include <fmt/core.h>

Maze::Maze(int rows, int cols) : m_maze(static_cast<unsigned long>(rows), std::vector<Cell>(
        static_cast<unsigned long>(cols))), m_rows(rows) , m_cols(cols) {
    fmt::print("Creating Maze of size {}x{}\n", rows, cols);
    initializeMaze();
    generateMaze();
    fmt::print("Maze created and generated.\n");
}

void Maze::initializeMaze() {
    m_maze.resize(static_cast<std::size_t>(m_rows), std::vector<Cell>(static_cast<std::size_t>(m_cols)));
    for (auto& row : m_maze) {
        for (auto& cell : row) {
            cell.visited = false;
            cell.topWall = true;
            cell.leftWall = true;
            cell.bottomWall = true;
            cell.rightWall = true;
        }
    }
}

void Maze::generateMaze() {
    generateMazeRecursive(0, 0);
    for (int r = 0; r < std::min(3, m_rows); ++r) {
        for (int c = 0; c < std::min(3, m_cols); ++c) {
            fmt::print("Cell[{},{}]: Top:{} Left:{} Bottom:{} Right:{}\n",
                       r, c,
                       m_maze[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].topWall,
                       m_maze[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].leftWall,
                       m_maze[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].bottomWall,
                       m_maze[static_cast<unsigned long>(r)][static_cast<unsigned long>(c)].rightWall);
        }
    }
}

void Maze::generateMazeRecursive(std::size_t r, std::size_t c) {
    fmt::print("Generating maze at cell [{}, {}]\n", r, c);
    std::vector<std::pair<std::ptrdiff_t , std::ptrdiff_t>> directions = {{1,0}, {-1,0}, {0,1},{0,-1}};
    std::random_shuffle(directions.begin(), directions.end());
    m_maze[r][c].visited = true;

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

        if(newR < static_cast<std::size_t>(m_rows) && newC < static_cast<std::size_t>(m_cols) && !m_maze[newR][newC].visited){
            if(dr == -1){
                m_maze[r][c].topWall = false;
                m_maze[newR][newC].bottomWall = false;
            }
            if(dr == 1){
                m_maze[r][c].bottomWall = false;
                m_maze[newR][newC].topWall = false;
            }
            if(dc == -1){
                m_maze[r][c].leftWall = false;
                m_maze[newR][newC].rightWall = false;
            }
            if(dc == 1){
                m_maze[r][c].rightWall = false;
                m_maze[newR][newC].leftWall = false;
            }
            generateMazeRecursive(newR, newC);
        }
    }
}

const std::vector<std::vector<Maze::Cell>>& Maze::getMaze() const {
    return m_maze;
}
