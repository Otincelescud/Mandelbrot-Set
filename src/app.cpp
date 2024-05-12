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

void App::set_pixel_color(SDL_Surface* surface, int pixel_x, int pixel_y, int r, int g, int b) {
    Uint32 *pixel = (Uint32*)((Uint8*)surface->pixels + pixel_y * surface->pitch + pixel_x * sizeof(Uint32));
    *pixel = SDL_MapRGB(surface->format, r, g, b);
}

// This function is subject to change
void App::set_background() {
    SDL_LockSurface(screen_surface);

    Complex *cnum = new Complex();
    for (int pixel_y = 0; pixel_y < HEIGHT; pixel_y++) {
        for (int pixel_x = 0; pixel_x < WIDTH; pixel_x++) {

            // Associates a complex number to each pixel
            MdbSetMath::px_pos_to_cnum(&pixel_x, &pixel_y, &pan, &zoom, cnum);

            // Set pixel to black if it's part of Mandelbrot Set
            if (MdbSetMath::is_part_of_mdb_set(cnum, MAX_ITERATIONS)) set_pixel_color(screen_surface, pixel_x, pixel_y, 0, 0, 0);

            // The higher the abs of the real value of the complex num, the more green the pixel associated with this value is
            // The higher the abs of the imaginary value of the complex num, the more red the pixel associated with this value is
            else set_pixel_color(screen_surface, pixel_x, pixel_y, int(255.0 - 255.0/(abs(cnum->getReal()*0.75)+1)), int(255.0 - 255.0/(abs(cnum->getImaginary()*0.75)+1)), 0);
        }
    }
    delete cnum;

    SDL_UnlockSurface(screen_surface);
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