//
// Created by daily on 25-12-23.
//
#ifndef ALGOVISUALIZER_SQUARE_HPP
#define ALGOVISUALIZER_SQUARE_HPP
#include "IRenderable.hpp"
class Square : public IRenderable{
public:
    Square(int x, int y, int size, SDL_Color color);
    void update() override;
    void render(SDL_Renderer* renderer) override;
    void setScreenDimensions(int screenWidth, int screenHeight);
private:
    int x_;
    int y_;
    int size_;
    SDL_Color color_;
    int velocityX_;
    int velocityY_;
    int screenWidth_;
    int screenHeight_;
};
#endif //ALGOVISUALIZER_SQUARE_HPP