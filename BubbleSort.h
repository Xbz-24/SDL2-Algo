//
// Created by daily on 03-01-24.
//

#ifndef ALGOVISUALIZER_BUBBLESORT_H
#define ALGOVISUALIZER_BUBBLESORT_H
#include "IRenderable.hpp"
#include <vector>
class BubbleSort : public IRenderable{
public:
    BubbleSort(int dataSize);
    void update() override;
    void render(SDL_Renderer* renderer) override;
    void startSort();
    void setScreenDimensions(int width, int height);

private:
    std::vector<int> data;
    int currentIdx;
    bool sorting;
    int dataSize_;
    int screenWidth;
    int screenHeight;
    int comparisonIdx;
    bool swappedInLastPass;
    int sortedCount;
    int lastSwapIndex;
    unsigned long long swapCount;
    unsigned long long comparisonCount;
    bool finalIterationStarted;
    int finalIterationCount;
    bool greenIterationStarted;
    bool whiteIterationStarted;
    int iterationCount;
    bool isComplete;
};


#endif //ALGOVISUALIZER_BUBBLESORT_H
