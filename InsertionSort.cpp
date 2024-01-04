//
// Created by daily on 04-01-24.
//

#include "InsertionSort.h"

#include "Constants.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

InsertionSort::InsertionSort(int dataSize) :
data(),
currentIndex(1),
keyIndex(0),
sorting(false),
dataSize_(dataSize),
screenWidth(0),
screenHeight(0),
isComplete(false)
{
    srand(static_cast<unsigned>(time(nullptr)));
    for(int i = 0; i < dataSize; i++){
        int val = (rand() % 99) + 1;
        data.push_back(val);
    }
}

void InsertionSort::update() {
    if (isComplete) return;
    if (!sorting) {
        sorting = true;
        return;
    }

    if (currentIndex < dataSize_) {
        int key = data[static_cast<size_t>(currentIndex)];
        keyIndex = currentIndex - 1;

        while (keyIndex >= 0 && data[static_cast<unsigned long>(keyIndex)] > key) {
            data[static_cast<size_t>(keyIndex + 1)] = data[static_cast<size_t>(keyIndex)];
            keyIndex--;
        }
        data[static_cast<size_t>(keyIndex + 1)] = key;
        currentIndex++;
    } else {
        isComplete = true;
        sorting = false;
    }

}

void InsertionSort::render(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int barWidth = (screenWidth * 2) / (dataSize_ * 2) - 2;
    for (int i = 0; i < dataSize_; ++i) {
        int barHeight = data[static_cast<size_t>(i)] * (screenHeight / 100);
        int barTop = screenHeight - barHeight;

        // Change color based on the state
        if (i == currentIndex) {
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange for the current index
        } else if (i <= currentIndex) {
            SDL_SetRenderDrawColor(renderer, 124, 252, 0, 255); // Lawn green for sorted part
        } else {
            SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // Light blue for unsorted part
        }

        SDL_Rect rect = {i * (barWidth + 2), barTop, barWidth, barHeight};
        SDL_RenderFillRect(renderer, &rect);
    }

    // Additional rendering for text information can go here

    SDL_RenderPresent(renderer);
}


void InsertionSort::startSort() {
    sorting = true;
    currentIndex = 1;
}

void InsertionSort::setScreenDimensions(int width, int height) {
    screenWidth = width;
    screenHeight = height;
}
