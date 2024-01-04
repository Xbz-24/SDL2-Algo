//
// Created by daily on 03-01-24.
//

#include "Block.h"

Block::Block(int xPos, int yPos, int blockType) : x(xPos), y(yPos), type(blockType){}

int Block::getType() const{
    return type;
}
void Block::setX(int newX){
    x = newX;
}
void Block::setY(int newY){
    y = newY;
}
void Block::setType(int newType){
    type = newType;
}