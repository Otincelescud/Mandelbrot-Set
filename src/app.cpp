#include "app.h"

App::App(const int width, const int height, const int max_iterations) : WIDTH(width), HEIGHT(height), MAX_ITERATIONS(max_iterations) {}
App::~App() {}

void App::init(const char *title, int xpos, int ypos, bool fullscreen) {
    int flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        window = SDL_CreateWindow(title, xpos, ypos, WIDTH, HEIGHT, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        SDL_GLContext glContext = SDL_GL_CreateContext(window);

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            SDL_Log("Failed to initialize OpenGL context.");
        }

        cnt = 0;
        is_running = true;
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
}

void App::render() {
    glClearColor(0.5f, 0.1f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
}

void App::clean() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool App::running() { return is_running; }