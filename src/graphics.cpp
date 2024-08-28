#include "graphics.h"

SDL_Window *GPU_Graphics::window = nullptr;
SDL_GLContext GPU_Graphics::gl_context;

bool GPU_Graphics::create_window(const char* w_title, int w_xpos, int w_ypos, const int w_WIDTH, const int w_HEIGHT, int w_flags) {
    window = SDL_CreateWindow(w_title,
                                w_xpos, w_ypos,
                                w_WIDTH, w_HEIGHT,
                                w_flags);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    return true;
}

bool GPU_Graphics::create_GL_context() {
    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_Log("Failed to create OpenGL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return false;
    }
    return true;
}

bool GPU_Graphics::init_GL() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_Log("Failed to initialize OpenGL context with glad");
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        return false;
    }
    return true;
}

bool GPU_Graphics::init_graphics(const char* w_title, int w_xpos, int w_ypos, const int w_WIDTH, const int w_HEIGHT, int w_flags) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (create_window(w_title, w_xpos, w_ypos, w_WIDTH, w_HEIGHT, w_flags) && create_GL_context() && init_GL()) return true;
    return false;
}

void GPU_Graphics::render() {
    glClearColor(0.5f, 0.1f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
}

void GPU_Graphics::clean() {
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
}