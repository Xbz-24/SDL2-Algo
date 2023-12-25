//
// Created by daily on 25-12-23.
//
#ifndef ALGOVISUALIZER_SQUARE_HPP
#define ALGOVISUALIZER_SQUARE_HPP
#include <SDL2/SDL.h>
class Square {
public:
    Square(int x, int y, int size, SDL_Color color);
    void update(int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer) const;
private:
    int x_;
    int y_;
    int size_;
    SDL_Color color_;
    int velocityX_;
    int velocityY_;
};
#endif //ALGOVISUALIZER_SQUARE_HPP