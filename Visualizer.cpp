/**
 * @file Visualizer.cpp
 * @brief
 * @date Created on 23-12-23
 * @author Renato Chavez
 */
#include "Visualizer.hpp"
#include "Constants.hpp"
#include "Maze.hpp"
#include <fmt/core.h>
#include <boost/log/trivial.hpp>
#include <utility>
/**
 * @brief Constructs a Visualizer object.
 * Initializes the Visualizer with given window parameters and initializes SDL components.
 * Catches and reports any SDL initialization errors.
 *
 * @param title
 * @param xpos
 * @param ypos
 * @param width
 * @param height
 * @param fullscreen
 */
Visualizer::Visualizer(const char* title, int xpos, int ypos, int width, int height, bool fullscreen):
        windowID_(0),
        maze_(nullptr),
        running_(false),
        sdlWindow_(nullptr),
        sdlRenderer_(nullptr),
        windowWidth_(width),
        windowHeight_(height),
        fpsFont_(nullptr) ,
        fpsCounter_(nullptr, nullptr),
        windowTitle_(title),
        windowPosX_(xpos),
        windowPosY_(ypos),
        isFullscreen_(fullscreen),
        squares_(),
        renderables_(),
        tetrisGame_(nullptr),
        isFocused(false)
        {
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(info) << "Initializing Visualizer with title: " << title;
#endif
    try{
        initializeSDLComponents();
        running_ = true;
    }
    catch(const std::runtime_error& e){
#ifndef ENABLE_LOGGING
        BOOST_LOG_TRIVIAL(error) << "Initialization error:" << e.what();
#endif
        running_ = false;
        return;
    }
}
/**
 * @brief Destructor for the Visualizer.
 * Cleans up resources used by the Visualizer.
 */
Visualizer::~Visualizer() {
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(info) << "Cleaning up Visualizer resources.";
#endif
    clean();
}
/**
 * @brief Checks if the visualizer is running.
 * @return True if the visualizer is currently running, false otherwise.
 */
bool Visualizer::running() const{
    return running_;
}
/**
 * @brief Initializes all SDL components used by the Visualizer.
 */
void Visualizer::initializeSDLComponents(){
    //initializeSDL();
    createWindow();
    createRenderer();
    initializeTTF();
    fpsCounter_ = FPSCounter(sdlRenderer_, fpsFont_);
}
/**
 * @brief Initializes the SDL library.
 */
void Visualizer::initializeSDL(){
    if(SDL_Init(Constants::SDL_INIT_FLAGS) != 0){
#ifndef ENABLE_LOGGING
        BOOST_LOG_TRIVIAL(error) << "SDL could not initialize" << SDL_GetError();
#endif
        throw std::runtime_error(fmt::format("{}{}", Constants::SDL_INIT_ERROR, SDL_GetError()));
    }
}
/**
 * @brief Creates the SDL window based on the stored parameters.
 */
void Visualizer::createWindow(){
    Uint32 flags = isFullscreen_ ? SDL_WINDOW_MAXIMIZED : 0;
    sdlWindow_ = SDL_CreateWindow(windowTitle_, windowPosX_, windowPosY_, windowWidth_, windowHeight_, flags);
    windowID_ = SDL_GetWindowID(sdlWindow_);
    if(!sdlWindow_){
#ifndef ENABLE_LOGGING
        BOOST_LOG_TRIVIAL(error) << "Failed to create sdlWindow_" << SDL_GetError();
#endif
        throw std::runtime_error(fmt::format("{}{}", Constants::WINDOW_CREATION_ERROR, SDL_GetError()));
    }
}
/**
 * @brief Creates an SDL renderer for the window.
 */
void Visualizer::createRenderer(){
    sdlRenderer_ = SDL_CreateRenderer(sdlWindow_, -1, SDL_RENDERER_SOFTWARE);
    if(!sdlRenderer_){
#ifndef ENABLE_LOGGING
        BOOST_LOG_TRIVIAL(error) << "Failed to create sdlRenderer_" << SDL_GetError();
#endif
        throw std::runtime_error(fmt::format("{}{}", Constants::RENDERER_CREATION_ERROR, SDL_GetError()));
    }
    SDL_SetRenderDrawColor(sdlRenderer_, Constants::RENDER_COLOR_R, Constants::RENDER_COLOR_G, Constants::RENDER_COLOR_B, Constants::RENDER_COLOR_A);
}
/**
 * @brief Initializes the SDL_ttf library for font rendering.
 */
void Visualizer::initializeTTF(){
    if(TTF_Init() == -1){
#ifndef ENABLE_LOGGING
        BOOST_LOG_TRIVIAL(error) << "SDL_ttf could not initialize" << TTF_GetError();
#endif
        throw std::runtime_error(fmt::format("{}{}",Constants::FONT_LOAD_ERROR, TTF_GetError()));
    }
    fpsFont_ = TTF_OpenFont(Constants::FONT_PATH, Constants::FONT_SIZE);
    if(!fpsFont_){
#ifndef ENABLE_LOGGING
        BOOST_LOG_TRIVIAL(error) << "Failed to load font" << TTF_GetError();
#endif
        throw std::runtime_error(fmt::format("{}{}",Constants::FONT_LOAD_ERROR ,TTF_GetError()));
    }
}
/**
 * @brief Handles SDL events, such as window closing.
 */
void Visualizer::handleEvents() {
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(trace) << "Handling SDL events.";
#endif
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_WINDOWEVENT && event.window.windowID == windowID_) {
            if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
                isFocused = true;
            } else if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
                isFocused = false;
            }
        }
        if(event.type == SDL_QUIT){
            running_ = false;
        }
        if(!isFocused || event.window.windowID != windowID_) continue;

        switch(event.type){
            case SDL_QUIT:
#ifndef ENABLE_LOGGING
                BOOST_LOG_TRIVIAL(info) << "Received SDL_QUIT event.";
#endif
                running_ = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_LEFT:
                        tetrisGame_->movePieceLeft();
                        break;
                    case SDLK_RIGHT:
                        tetrisGame_->movePieceRight();
                        break;
                    case SDLK_UP:
                        tetrisGame_->rotatePiece();
                        break;
                    case SDLK_DOWN:
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_RIGHT){
                    running_ = false;
                }
                if(event.button.button == SDL_BUTTON_LEFT){
                    std::cout << "Mouse Clicked at: X=" << event.button.x << ", Y=" << event.button.y << std::endl;
                    if(maze_) {
                        maze_->handleMouseClick(event.button.x, event.button.y, sdlWindow_);
                    } else {
                        std::cout << "Maze object is null." << std::endl;
                    }
                }
                break;
            default:
                break;
        }
    }
}
/**
 * @brief Updates the state of the visualizer.
 * Currently empty, but will be used for future state updates.
 */
void Visualizer::update() {
    for(auto& renderable: renderables_){
        renderable->update();
    }
}
/**
 * @brief Renders the current frame to the window.
 * This includes clearing the renderer, drawing the maze and the FPS counter, and presenting the renderer.
 */
void Visualizer::render() {
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(debug) << "Rendering frame.";
#endif
//    SDL_SetRenderDrawColor(sdlRenderer_, 128, 0, 32, 255);
    SDL_SetRenderDrawColor(sdlRenderer_, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer_);

    for(const auto& renderable : renderables_){
        renderable->render(sdlRenderer_);
    }
    fpsCounter_.update();
    fpsCounter_.render();

    SDL_RenderPresent(sdlRenderer_);
#ifndef ENABLE_LOGGING
    BOOST_LOG_TRIVIAL(debug) << "Frame rendered.";
#endif
}
/**
 * @brief Cleans up all SDL-related resources.
 * This includes closing the font, destroying the renderer, and destroying the window.
 */
void Visualizer::clean() {
    if(fpsFont_){
        TTF_CloseFont(fpsFont_);
    }
    if(sdlRenderer_){
        SDL_DestroyRenderer(sdlRenderer_);
    }
    if(sdlWindow_){
        SDL_DestroyWindow(sdlWindow_);
    }
}
/**
 * @brief Sets the maze to be rendered by the visualizer.
 * @param maze Shared pointer to the Maze object to be visualized.
 */
void Visualizer::setMaze(std::shared_ptr<Maze> maze) {
    maze_ = std::move(maze);
    //mazeRenderer_ = std::make_unique<MazeRenderer>(maze_, sdlRenderer_);
}
void Visualizer::addRenderable(std::shared_ptr<IRenderable> renderable) {
    renderables_.push_back(renderable);
}
void Visualizer::setTetris(std::shared_ptr<Tetris> tetris) {
    tetrisGame_ = std::move(tetris);
}
