#include "app.h"

App::App(const int width, const int height, const int max_iterations) : WIDTH(width), HEIGHT(height), MAX_ITERATIONS(max_iterations) {}
App::~App() {}

bool App::init(const char *title, int xpos, int ypos, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        if (!GPU_Graphics::init_graphics(title, xpos, ypos, WIDTH, HEIGHT, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) {
            SDL_Quit();
            is_running = false;
            return false;
        }

        cnt = 0;
        is_running = true;
    }
    else {
        is_running = false;
        std::cout << "Can't initialise SDL2\n";
        return false;
    }

    zoom = 6 / (long double)WIDTH;
    pan.setReal(-3);
    pan.setImaginary((long double)HEIGHT/2*zoom);
    return true;
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
}

void App::clean() {
    GPU_Graphics::clean();
    SDL_Quit();
}

bool App::running() { return is_running; }