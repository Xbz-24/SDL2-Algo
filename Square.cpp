//
// Created by daily on 25-12-23.
//
#include "Square.hpp"

Square::Square(int x, int y, int size, SDL_Color color):
x_(x),
y_(y),
size_(size),
color_(color),
velocityX_(10 - size / 10),
velocityY_(10 - size / 10),
screenWidth_(0),
screenHeight_(0)
{

}

void Square::update(){
    x_ += velocityX_;
    y_ += velocityY_;
    if(x_ <= 0 || x_ + size_ >= screenWidth_){
        velocityX_ = -velocityX_;
    }
    if(y_ <= 0 || y_ + size_ >= screenHeight_){
        velocityY_ = -velocityY_;
    }
}

void Square::render(SDL_Renderer* renderer) {
    SDL_Rect rect = {x_, y_ ,size_, size_};
    SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
    SDL_RenderFillRect(renderer, &rect);
}
void Square::setScreenDimensions(int screenWidth, int screenHeight) {
    screenWidth_ = screenWidth;
    screenHeight_ = screenHeight;
}