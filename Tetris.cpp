//
// Created by daily on 03-01-24.
//
#include "Tetris.h"
#include <algorithm>
#include <iostream>

Tetris::Tetris() :
    grid(gridHeight, std::vector<int>(gridWidth, 0)),
    gameOver(false),
    score(0),
    currentPiece(0),
    screenHeight(0),
    screenWidth(0),
    lastDropTime(SDL_GetTicks()){
    startNewGame();
}
void Tetris::update(){
    if(isGameOver()){
        return;
    }
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastDropTime >= 1000) {
        dropPiece();
        lastDropTime = currentTime;
    }
}
void Tetris::render(SDL_Renderer* renderer) {
    if (gameOver) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < gridHeight; y++) {
        for (int x = 0; x < gridWidth; x++) {
            SDL_Rect rect = {x * cellSize, y * cellSize, cellSize, cellSize};
            if (grid[static_cast<size_t>(y)][static_cast<size_t>(x)] != 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }

    for (const auto& block : currentPiece.getBlocks()) {
        SDL_Rect rect = {block.getX() * cellSize, block.getY() * cellSize, cellSize, cellSize};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

    }
    SDL_RenderPresent(renderer);
}

void Tetris::startNewGame() {
    srand(static_cast<unsigned>(time(nullptr)));

    gameOver = false;
    score = 0;

    for(auto& row : grid){
        std::fill(row.begin(), row.end(), 0);
    }
    generateNewPiece();
}
void Tetris::movePieceLeft() {
    bool canMoveLeft = true;
    for(const auto& block : currentPiece.getBlocks()){
        int newX = block.getX() - 1;
        if(newX < 0 || grid[static_cast<unsigned long>(block.getY())][static_cast<unsigned long>(newX)] != 0){
            canMoveLeft = false;
            break;
        }
    }
    if(canMoveLeft){
        for(auto& block : currentPiece.getBlocks()){
            block.setX(block.getX() - 1);
        }
    }
}
void Tetris::movePieceRight() {
    bool canMoveRight = true;
    for(const auto& block : currentPiece.getBlocks()){
        int newX = block.getX() + 1;
        if(newX >= gridWidth || grid[static_cast<unsigned long>(block.getY())][static_cast<unsigned long>(newX)] != 0){
            canMoveRight = false;
            break;
        }
    }
    if(canMoveRight){
        for(auto& block: currentPiece.getBlocks()){
            block.setX(block.getX() + 1);
        }
    }
}
void Tetris::rotatePiece() {
    auto& pivot = currentPiece.getBlocks()[0];
    bool canRotate = true;

    std::vector<Block> rotatedPositions;
    for(const auto& block : currentPiece.getBlocks()){
        int rotatedX = pivot.getX() - (block.getY() - pivot.getY());
        int rotatedY = pivot.getY() - (block.getX() - pivot.getX());

        if(rotatedX < 0 || rotatedX >= gridWidth || rotatedY < 0 || rotatedY >= gridHeight || grid[static_cast<unsigned long>(rotatedY)][static_cast<unsigned long>(rotatedX)] != 0){
            canRotate = false;
            break;
        }
        int pivotType = currentPiece.getType();
        rotatedPositions.push_back(Block(rotatedX, rotatedY, pivotType));

        if(canRotate){
            currentPiece.setBlocks(rotatedPositions);
        }
    }
}
void Tetris::dropPiece() {
    bool canDrop = true;
    for (const auto& block : currentPiece.getBlocks()) {
        if (block.getY() + 1 >= gridHeight || grid[static_cast<unsigned long>(block.getY() + 1)][static_cast<unsigned long>(block.getX())] != 0) {
            canDrop = false;
            break;
        }
    }
    if (canDrop) {
        currentPiece.dropBlocks();
    }
    else {
        placePiece();
        generateNewPiece();
    }
}

bool Tetris::isGameOver() const {
    for (const auto& block : currentPiece.getBlocks()) {
        if (grid[static_cast<unsigned long>(block.getY())][static_cast<unsigned long>(block.getX())] != 0) {
            return true;
        }
    }
    return false;
}

int Tetris::getScore() const {
    return score;
}
void Tetris::checkLineClear() {
    int linesCleared = 0;
    for (int y = 0; y < gridHeight; y++) {
        bool lineFull = true;
        for (int x = 0; x < gridWidth; x++) {
            if (grid[static_cast<size_t>(y)][static_cast<size_t>(x)] == 0) {
                lineFull = false;
                break;
            }
        }

        if (lineFull) {
            linesCleared++;
            for (int row = y; row > 0; row--) {
                grid[static_cast<size_t>(row)] = grid[static_cast<size_t>(row - 1)];
            }
            grid[0] = std::vector<int>(gridWidth, 0);
        }
    }

    score += linesCleared * 100;
}

void Tetris::generateNewPiece() {
    currentPiece = getRandomPiece();
    if (isGameOver()) {
        gameOver = true;
    }
}

void Tetris::placePiece() {
    for (const auto& block : currentPiece.getBlocks()) {
        grid[static_cast<size_t>(block.getY())][static_cast<size_t>(block.getX())] = currentPiece.getType();
    }
    checkLineClear();
}
Piece Tetris::getRandomPiece(){
    int type = rand() % 7;
    std::vector<Block> blocks;
    switch (type) {
        case 0:
            blocks = {Block(3, 0, type), Block(4, 0, type), Block(5, 0, type), Block(6, 0, type)};
            break;
        case 1:
            blocks = {Block(4, 0, type), Block(5, 0, type), Block(4, 1, type), Block(5, 1, type)};
            break;
        case 2:
            blocks = {Block(3, 0, type), Block(4, 0, type), Block(5, 0, type), Block(4, 1, type)};
            break;
        case 3:
            blocks = {Block(4, 0, type), Block(5, 0, type), Block(3, 1, type), Block(4, 1, type)};
            break;
        case 4:
            blocks = {Block(3, 0, type), Block(4, 0, type), Block(4, 1, type), Block(5, 1, type)};
            break;
        case 5:
            blocks = {Block(3, 0, type), Block(3, 1, type), Block(4, 1, type), Block(5, 1, type)};
            break;
        case 6:
            blocks = {Block(5, 0, type), Block(3, 1, type), Block(4, 1, type), Block(5, 1, type)};
            break;
        default:
            break;
    }
    return Piece(blocks, type);
}

void Tetris::setScreenDimensions(int width, int height) {
    screenWidth = width;
    screenHeight = height;
}