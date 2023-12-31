/**
 * @file Visualizer.hpp
 * @brief Include dependencies for the Visualizer class.
 * @date Created on 23-12-23.
 * @author Renato Chavez
 */
#ifndef ALGOVISUALIZER_VISUALIZER_HPP
#define ALGOVISUALIZER_VISUALIZER_HPP
/**
 * @brief SDL2 main header for window, rendering, and event handling.
 */
#include "SDL2/SDL.h"
/**
 * @brief SDL2 extension for TrueType font rendering.
 */
#include "SDL2/SDL_ttf.h"
/**
 * @brief Standard IO stream objects.
 */
#include <iostream>
/**
 * @brief Maze class for maze representation and management.
 */
#include "Maze.hpp"
/**
 * @brief FPSCounter class for rendering frames per second information.
 */
#include "FPSCounter.hpp"
/**
 * @brief MazeRenderer class for visualizing the maze.
 */
#include "Square.hpp"
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
    void addRenderable(std::shared_ptr<IRenderable> renderable);
    [[nodiscard]] SDL_Window* getWindow() const {
        return sdlWindow_;
    }


private:
    Uint32 windowID_;
    /**
     * @brief Initializes the SDl library.
     */
    static void initializeSDL();
    /**
     * @brief Creates the SDL window based on stored parameters.
     */
    void createWindow();
    /**
     * @brief Creates a SDL renderer for the window.
     */
    void createRenderer();
    /**
     * @brief Initializes the SDL_ttf library for font rendering.
     */
    void initializeTTF();
    /**
     * @brief Initializes all SDL components used by the Visualizer.
     */
    void initializeSDLComponents();

    /**
     * @brief Shared pointer to the maze being visualized.
     */
    std::shared_ptr<Maze> maze_;
    /**
     * @brief Flag indicating whether the visualizer is running.
     */
    bool running_;
    /**
     * @brief Pointer to the SDL window.
     */
    SDL_Window *sdlWindow_;
    /**
     * @brief Pointer to the SDL renderer
     */
    SDL_Renderer *sdlRenderer_;
    /**
     * @brief Width of the SDL window.
     */
    int windowWidth_;
    /**
     * @brief Height of the SDL window.
     */
    int windowHeight_;
    /**
     * @brief Pointer to the TTF font used for rendering text.
     */
    TTF_Font *fpsFont_;
    /**
     * @brief FPSCounter object for displaying frame rate.
     */
    FPSCounter fpsCounter_;
    /**
     * @brief Renderer for the maze.
     */
    //std::unique_ptr<MazeRenderer> mazeRenderer_;
    /**
     * @brief Title of the SDL window.
     */
    const char* windowTitle_;
    /**
     * @brief X-position of the SDL window.
     */
    int windowPosX_;
    /**
     * @brief Y-position of the SDL window.
     */
    int windowPosY_;
    /**
     * @brief Indicates if the window is fullscreen.
     */
    bool isFullscreen_;
    std::vector<Square> squares_;
    std::vector<std::shared_ptr<IRenderable>> renderables_;
};
#endif //ALGOVISUALIZER_VISUALIZER_HPP