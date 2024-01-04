//
// Created by daily on 03-01-24.
//
#include "Piece.h"

Piece::Piece(int pieceType) : blocks(), type(pieceType) {
    blocks.emplace_back(0, 0, type);
    blocks.emplace_back(0, 1, type);
    blocks.emplace_back(1, 0, type);
    blocks.emplace_back(1, 1, type);
}
Piece::Piece(const std::vector<Block>& newBlocks, int newType): blocks(newBlocks), type(newType){

}
void Piece::rotate() {
    Block pivot = blocks[0];
    for (auto& block : blocks) {
        int newX = pivot.getX() - (block.getY() - pivot.getY());
        int newY = pivot.getY() + (block.getX() - pivot.getX());
        block.setX(newX);
        block.setY(newY);
    }
}

void Piece::moveLeft() {
    for (auto& block : blocks) {
        block.setX(block.getX() - 1);
    }
}
void Piece::moveRight() {
    for (auto& block : blocks) {
        block.setX(block.getX() + 1);
    }
}
std::vector<Block> Piece::getBlocks() const {
    return blocks;
}
int Piece::getType() const {
    return type;
}
void Piece::setBlocks(const std::vector<Block>& newBlocks){
    blocks = newBlocks;
}
void Piece::dropBlocks() {
    for (auto& block : blocks) {
        block.setY(block.getY() + 1);
    }
}
