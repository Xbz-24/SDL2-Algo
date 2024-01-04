//
// Created by daily on 03-01-24.
//

#ifndef ALGOVISUALIZER_PIECE_H
#define ALGOVISUALIZER_PIECE_H
#include <vector>
#include "Block.h"

class Piece {
public:
    Piece(int type);
    Piece(const std::vector<Block>& newBlocks, int newType);
    void rotate();
    void moveLeft();
    void moveRight();
    std::vector<Block> getBlocks() const;
    int getType() const;
    void setBlocks(const std::vector<Block>& newBlocks);
    void dropBlocks();

private:
    std::vector<Block> blocks;
    int type;
};


#endif //ALGOVISUALIZER_PIECE_H
