//
// Created by daily on 23-12-23.
//

#include "Visualizer.hpp"
#include <fmt/core.h>

Visualizer::Visualizer(const char* title, int xpos, int ypos, int width, int height, bool fullscreen):
        maze_(nullptr),
        running_(false),
        sdlWindow_(nullptr),
        sdlRenderer_(nullptr),
        windowWidth_(width),
        windowHeight_(height),
        fpsFont_(nullptr) ,
        fpsCounter_(nullptr, nullptr),
        mazeRenderer_(nullptr),
        windowTitle_(title),
        windowPosX_(xpos),
        windowPosY_(ypos),
        isFullscreen_(fullscreen){
    try{
        initializeSDLComponents();
        running_ = true;
    }
    catch(const std::runtime_error& e){
        std::cerr << "Initialization error: " << e.what() << std::endl;
        running_ = false;
        return;
    }
}

Visualizer::~Visualizer() {
    clean();
}

bool Visualizer::running() const{
    return running_;
}
void Visualizer::initializeSDLComponents(){
    initializeSDL();
    createWindow();
    createRenderer();
    initializeTTF();
    mazeRenderer_ = std::make_unique<MazeRenderer>(maze_, sdlRenderer_);
    fpsCounter_ = FPSCounter(sdlRenderer_, fpsFont_);
}
void Visualizer::initializeSDL(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        throw std::runtime_error(fmt::format("SDL could not initialize: {}", SDL_GetError()));
    }
}
void Visualizer::createWindow(){
    Uint32 flags = isFullscreen_ ? SDL_WINDOW_MAXIMIZED : 0;
    sdlWindow_ = SDL_CreateWindow(windowTitle_, windowPosX_, windowPosY_, windowWidth_, windowHeight_, flags);
    if(!sdlWindow_){
        throw std::runtime_error(fmt::format("Failed to create sdlWindow_: {}", SDL_GetError()));
    }
}
void Visualizer::createRenderer(){
    sdlRenderer_ = SDL_CreateRenderer(sdlWindow_, -1, SDL_RENDERER_ACCELERATED);
    if(!sdlRenderer_){
        throw std::runtime_error(fmt::format("Failed to create sdlRenderer_: {}", SDL_GetError()));
    }
    SDL_SetRenderDrawColor(sdlRenderer_, 255, 255, 255, 255);
}
void Visualizer::initializeTTF(){
    if(TTF_Init() == -1){
        throw std::runtime_error(fmt::format("SDL_ttf could not initialize: {}", TTF_GetError()));
    }
    fpsFont_ = TTF_OpenFont("../fonts/HackNerdFont-Regular.ttf", 24);
    if(!fpsFont_){
        throw std::runtime_error(fmt::format("Failed to load font: {}", TTF_GetError()));
    }
}
void Visualizer::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            running_ = false;
            break;
        default:
            break;
    }
}
void Visualizer::update() {

}
void Visualizer::render() {
    fmt::print("Rendering frame...\n");
    SDL_SetRenderDrawColor(sdlRenderer_, 128, 0, 32, 255);
    SDL_RenderClear(sdlRenderer_);

    mazeRenderer_->render(windowWidth_, windowHeight_);
    fpsCounter_.update();
    fpsCounter_.render();

    SDL_RenderPresent(sdlRenderer_);
    fmt::print("Frame rendered.\n");
}
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

void Visualizer::setMaze(std::shared_ptr<Maze> maze) {
    maze_ = maze;
    mazeRenderer_ = std::make_unique<MazeRenderer>(maze_, sdlRenderer_);
}