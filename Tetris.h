//
// Created by daily on 03-01-24.
//

#ifndef ALGOVISUALIZER_TETRIS_H
#define ALGOVISUALIZER_TETRIS_H
#include "IRenderable.hpp"
#include "Piece.h"
#include <vector>
#include <SDL2/SDL.h>
#include <chrono>

class Tetris : public IRenderable{
public:
    Tetris();
    virtual ~Tetris() = default;

    void update() override;
    void render(SDL_Renderer* renderer) override;
    void startNewGame();
    void movePieceLeft();
    void movePieceRight();
    void rotatePiece();
    void dropPiece();
    bool isGameOver() const;
    int getScore() const;
    void setScreenDimensions(int width, int height);

private:
    const int NUM_PIECES_TYPES = 7;
    static const int gridWidth = 10;
    static const int gridHeight = 20;
    const int cellSize = 30;

    std::vector<std::vector<int>> grid;
    bool gameOver;
    bool score;
    void checkLineClear();
    void generateNewPiece();
    void placePiece();
    Piece currentPiece;
    Piece getRandomPiece();
    int screenHeight;
    int screenWidth;
    Uint32 lastDropTime;
};


#endif //ALGOVISUALIZER_TETRIS_H
