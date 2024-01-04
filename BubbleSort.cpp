//
// Created by daily on 03-01-24.
//
#include "BubbleSort.h"
#include "Constants.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

BubbleSort::BubbleSort(int dataSize) :
    data(),
    currentIdx(0),
    sorting(false),
    dataSize_(dataSize),
    screenWidth(0),
    screenHeight(0),
    comparisonIdx(-1),
    swappedInLastPass(false),
    sortedCount(0),
    lastSwapIndex(dataSize-1),
    swapCount(0),
    comparisonCount(0),
    finalIterationStarted(false),
    finalIterationCount(0),
    greenIterationStarted(false),
    whiteIterationStarted(false),
    iterationCount(0),
    isComplete(false)
    {
    srand(static_cast<unsigned>(time(nullptr)));
    std::cout << "Constructor: dataSize_ = " << dataSize_ << ", screenWidth = " << screenWidth << ", screenHeight = " << screenHeight << std::endl;
    for(int i = 0; i < dataSize; i++){
        int val = (rand() % 99) + 1;
        data.push_back(val);
        std::cout << "Data[" << i << "] = " << val << std::endl;
    }
}
void BubbleSort::update() {
    if(isComplete) return;
    if (!sorting && !greenIterationStarted && !whiteIterationStarted) {
        greenIterationStarted = true;
    }
    if (greenIterationStarted) {
        iterationCount++;
        if (iterationCount > 1) {
            greenIterationStarted = false;
            whiteIterationStarted = true;
            iterationCount = 0;
            return;
        }
    }
    if (whiteIterationStarted) {
        iterationCount++;
        if (iterationCount > 1) {
            whiteIterationStarted = false;
            iterationCount = 0;
            isComplete = true;
            return;
        }
    }
    if (sorting) {
        if (currentIdx < dataSize_ - sortedCount - 1) {
            comparisonIdx = currentIdx;
            comparisonCount++;
            if (data[static_cast<size_t>(currentIdx + 1)] < data[static_cast<size_t>(currentIdx)]) {
                std::swap(data[static_cast<size_t>(currentIdx + 1)], data[static_cast<size_t>(currentIdx)]);
                swappedInLastPass = true;
                lastSwapIndex = currentIdx;
                swapCount++;
            }
            currentIdx++;
        } else {
            if (swappedInLastPass) {
                swappedInLastPass = false;
                currentIdx = 0;
                sortedCount++;
            } else {
                sorting = false;
                comparisonIdx = -1;
            }
        }
    }
}
void BubbleSort::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int barWidth = (screenWidth * 2) / (dataSize_ * 2) - 2;
    for (int i = 0; i < dataSize_; ++i) {
        int barHeight = data[static_cast<unsigned long>(i)] * (screenHeight / 100);
        int barTop = screenHeight - barHeight;

        if(isComplete){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else if (greenIterationStarted && !whiteIterationStarted) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        } else if (whiteIterationStarted && !greenIterationStarted) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        } else {
            if (i == comparisonIdx || i == comparisonIdx + 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            } else if (i >= dataSize_ - sortedCount) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
        }
        SDL_Rect rect = {i * (barWidth + 2), barTop, barWidth, barHeight};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_RenderPresent(renderer);
}
void BubbleSort::startSort() {
    sorting = true;
    currentIdx = 0;
    std::cout << "Started sorting." << std::endl;
}
void BubbleSort::setScreenDimensions(int width, int height){
    screenWidth = width;
    screenHeight = height;
    std::cout << "Set Screen Dimensions: screenWidth = " << screenWidth << ", screenHeight = " << screenHeight << std::endl;
}