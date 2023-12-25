//
// Created by daily on 23-12-23.
//

#ifndef ALGOVISUALIZER_VISUALIZER_HPP
#define ALGOVISUALIZER_VISUALIZER_HPP
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include "Maze.hpp"
#include "FPSCounter.hpp"
#include "MazeRenderer.hpp"
#include <memory>

/**
 * @brief Visualizer class for managing visualization tasks.
 *
 * This class encapsulates the functionality for visualizing mazes using SDL.
 * It handles the creation and management of SDL windows and renderers,
 * processes SDL events, and renders frames that include a maze and FPS counter.
 */

class Visualizer {
public:
    Visualizer() = delete;
    Visualizer(const Visualizer&) = delete;
    Visualizer& operator=(const Visualizer&) = delete;
    /**
     * @brief Constructs a Visualizer object.
     *
     * Initializes SDL components, creates a window and renderer, and sets up TTF for font rendering.
     *
     * @param windowTitle The title of the SDL window.
     * @param windowPosX The x-position of the SDL window.
     * @param windowPosY The y-position of the SDL window.
     * @param windowWidth The width of the SDL window.
     * @param windowHeight The height of the SDL window.
     * @param isFullscreen Whether the window should be fullscreen.
     * @throws std::runtime_error if initialization of any SDL component fails.
     */
    Visualizer(const char* windowTitle, int windowPosX, int windowPosY,
               int windowWidth, int windowHeight, bool isFullscreen);
    /**
     * @brief Destructor for the Visualizer
     *
     * Cleans up SDL resources, including the window, renderer, and font.
     */
    ~Visualizer();
    /**
     * @brief Processes SDL events.
     *
     * Currently handles the SDL_QUIT event to stop the application.
     */
    void handleEvents();
    /**
     * @brief Updates the state of the visualizer.
     *
     * This function currently does not perform any action but can be used
     * for future updates that require per-frame state changes.
     */
    void update();
    /**
     * @brief Renders the current frame.
     *
     * Clears the screen, renders the maze and the FPS counter, and presents the updated frame.
     */
    void render();
    /**
     * @brief Cleans up SDL resources.
     *
     * Destroys the SDL window, renderer, and closes the font.
     */
    void clean();
    /**
     * @brief Checks if the visualizer is running.
     * @param maze A shared pointer to the Maze object to be visualized.
     */
    void setMaze(std::shared_ptr<Maze> maze);
    /**
     * @brief Checks if the visualizer is running.
     * @return true if the visualizer is currently running, false otherwise.
     */
    [[nodiscard]] bool running() const;
private:
    void initializeSDL();
    void createWindow();
    void createRenderer();
    void initializeTTF();
    void initializeSDLComponents();

    std::shared_ptr<Maze> maze_;
    bool running_;
    SDL_Window *sdlWindow_;
    SDL_Renderer *sdlRenderer_;
    int windowWidth_;
    int windowHeight_;
    TTF_Font *fpsFont_;
    FPSCounter fpsCounter_;
    std::unique_ptr<MazeRenderer> mazeRenderer_;
    const char* windowTitle_;
    int windowPosX_;
    int windowPosY_;
    bool isFullscreen_;
};
#endif //ALGOVISUALIZER_VISUALIZER_HPP
