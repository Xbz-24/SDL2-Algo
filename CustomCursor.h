//
// Created by daily on 30-12-23.
//

#ifndef ALGOVISUALIZER_CUSTOMCURSOR_H
#define ALGOVISUALIZER_CUSTOMCURSOR_H


#include <SDL2/SDL.h>

void createAndSetCustomCursor();
void createAndSetCustomCursor() {
    const int cursorSize = 5; // Size of the cursor
    const int center = cursorSize / 2;
    const int radius = center - 50; // Radius of the circle

    Uint8 cursorData[cursorSize * cursorSize];
    Uint8 cursorMask[cursorSize * cursorSize];

    // Initialize cursor data and mask
    memset(cursorData, 0, sizeof(cursorData));
    memset(cursorMask, 0, sizeof(cursorMask));

    // Create a circle
    for (int y = 0; y < cursorSize; ++y) {
        for (int x = 0; x < cursorSize; ++x) {
            int dx = x - center;
            int dy = y - center;
            if (dx * dx + dy * dy <= radius * radius) {
                cursorData[y * cursorSize + x] = 1; // The cursor itself (black part)
                cursorMask[y * cursorSize + x] = 1; // The mask (white part)
            } else {
                cursorData[y * cursorSize + x] = 0; // Outside the circle
                cursorMask[y * cursorSize + x] = 0; // Make it transparent
            }
        }
    }

    // Create and set the SDL cursor
    SDL_Cursor* customCursor = SDL_CreateCursor(cursorData, cursorMask, cursorSize, cursorSize, center, center);
    SDL_SetCursor(customCursor);
}


#endif //ALGOVISUALIZER_CUSTOMCURSOR_H
