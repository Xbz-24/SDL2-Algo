//
// Created by daily on 04-01-24.
//

#ifndef ALGOVISUALIZER_INSERTIONSORT_H
#define ALGOVISUALIZER_INSERTIONSORT_H
#include "IRenderable.hpp"
#include <vector>

class InsertionSort : public IRenderable{

public:
    InsertionSort(int dataSize);
    void update() override;
    void render(SDL_Renderer* renderer) override;
    void startSort();
    void setScreenDimensions(int width, int height);

private:
    std::vector<int> data;
    int currentIndex;
    int keyIndex;
    bool sorting;
    int dataSize_;
    int screenWidth;
    int screenHeight;
    bool isComplete;
};


#endif //ALGOVISUALIZER_INSERTIONSORT_H
