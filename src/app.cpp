#include "app.h"

App::App(const int width, const int height, const int max_iterations) : WIDTH(width), HEIGHT(height), MAX_ITERATIONS(max_iterations) {}
App::~App() {}

void App::init(const char *title, int xpos, int ypos, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        window = SDL_CreateWindow(title, xpos, ypos, WIDTH, HEIGHT, flags);

        renderer = SDL_CreateRenderer(window, -1, 0);

        cnt = 0;
        is_running = true;

        screen_surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    }
    else is_running = false;

    zoom = 6 / (long double)WIDTH;
    pan.setReal(-3);
    pan.setImaginary((long double)HEIGHT/2*zoom);
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

// This function is subject to change
void App::set_background() {

}

void App::update() {
    cnt++;
    set_background();
    tex = SDL_CreateTextureFromSurface(renderer, screen_surface);
}

void App::render() {
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void App::clean() {
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(screen_surface);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool App::running() { return is_running; }