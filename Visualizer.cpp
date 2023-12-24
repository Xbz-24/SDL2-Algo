//
// Created by daily on 23-12-23.
//

#include "Visualizer.hpp"
#include <fmt/core.h>

Visualizer::Visualizer():
maze(nullptr),
isRunning(false),
window(nullptr),
renderer(nullptr),
windowWidth(0),
windowHeight(0),
fpsFont(nullptr) ,
fpsCounter(nullptr, nullptr),
mazeRenderer(nullptr){}

Visualizer::~Visualizer() {}

bool Visualizer::running() const{
    return isRunning;
}
void Visualizer::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    windowHeight = height;
    windowWidth = width;
    try{
        initializeSDLComponents(title,xpos,ypos,width,height,fullscreen);
    }
    catch(const std::runtime_error& e){
        std::cerr << "Initialization error: " << e.what() << std::endl;
        isRunning = false;
        return;
    }
    mazeRenderer = std::make_unique<MazeRenderer>(maze, renderer);
    fpsCounter = FPSCounter(renderer, fpsFont);
    isRunning = true;
}
void Visualizer::initializeSDLComponents(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    initSDL();
    createWindow(title, xpos, ypos, width, height, fullscreen);
    createRenderer();
    initTTF();
}
void Visualizer::initSDL(){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        throw std::runtime_error(fmt::format("SDL could not initialize: {}", SDL_GetError()));
    }
}
void Visualizer::createWindow(const char* title, int xpos, int ypos , int width, int height, bool fullscreen){
    Uint32 flags = fullscreen ? SDL_WINDOW_MAXIMIZED : 0;
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(!window){
        throw std::runtime_error(fmt::format("Failed to create window: {}", SDL_GetError()));
    }
}
void Visualizer::createRenderer(){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        throw std::runtime_error(fmt::format("Failed to create renderer: {}", SDL_GetError()));
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
void Visualizer::initTTF(){
    if(TTF_Init() == -1){
        throw std::runtime_error(fmt::format("SDL_ttf could not initialize: {}", TTF_GetError()));
    }
    fpsFont = TTF_OpenFont("../fonts/HackNerdFont-Regular.ttf", 24);
    if(!fpsFont){
        throw std::runtime_error(fmt::format("Failed to load font: {}", TTF_GetError()));
    }
}
void Visualizer::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}
void Visualizer::update() {
}
void Visualizer::render() {
    fmt::print("Rendering frame...\n");
    SDL_SetRenderDrawColor(renderer, 128, 0, 32, 255);
    SDL_RenderClear(renderer);

    mazeRenderer->render(windowWidth, windowHeight);
    fpsCounter.update();
    fpsCounter.render();

    SDL_RenderPresent(renderer);
    fmt::print("Frame rendered.\n");
}
void Visualizer::clean() {
    if(fpsFont){
        TTF_CloseFont(fpsFont);
    }
    if(renderer){
        SDL_DestroyRenderer(renderer);
    }
    if(window){
        SDL_DestroyWindow(window);
    }
}

void Visualizer::setMaze(std::shared_ptr<Maze> m) {
    maze = m;
    mazeRenderer = std::make_unique<MazeRenderer>(maze, renderer);
}
