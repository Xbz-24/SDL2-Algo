//
// Created by daily on 25-12-23.
//

#ifndef ALGOVISUALIZER_IRENDERABLE_HPP
#define ALGOVISUALIZER_IRENDERABLE_HPP
#include <SDL2/SDL.h>
class IRenderable{
public:
    virtual ~IRenderable() = default;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};
#endif //ALGOVISUALIZER_IRENDERABLE_HPP
