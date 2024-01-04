//
// Created by daily on 03-01-24.
//

#ifndef ALGOVISUALIZER_BLOCK_H
#define ALGOVISUALIZER_BLOCK_H


class Block {
public:
    Block(int x, int y, int type);
    int getX() const { return x; };
    int getY() const { return y; };
    int getType() const;

    void setX(int newX);
    void setY(int newY);
    void setType(int newType);
private:
    int x;
    int y;
    int type;
};


#endif //ALGOVISUALIZER_BLOCK_H
