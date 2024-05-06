#include "app.h"

App::App(const int width, const int height) : WIDTH(width), HEIGHT(height) {}
App::~App() {}

void App::init(const char *title, int xpos, int ypos, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        window = SDL_CreateWindow(title, xpos, ypos, WIDTH, HEIGHT, flags);

        renderer = SDL_CreateRenderer(window, -1, 0);

        cnt = 0;
        is_running = true;
    }
    else is_running = false;
}

void App::handle_events() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
}

void App::set_pixel_color(int pixel_x, int pixel_y, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, pixel_x, pixel_y);
}

void App::update() {
    cnt++;
}

void App::render() {
    SDL_RenderClear(renderer);
    // Render
    SDL_RenderPresent(renderer);
}

void App::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool App::running() { return is_running; }