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

void App::set_pixel_color(int pixel_x, int pixel_y, int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, pixel_x, pixel_y);
}

// This function is subject to change
void App::set_background() {
    Complex *cnum = new Complex();
    for (int pixel_y = 0; pixel_y < HEIGHT; pixel_y++) {
        for (int pixel_x = 0; pixel_x < WIDTH; pixel_x++) {

            // Associates a complex number to each pixel
            MdbSetMath::px_pos_to_cnum(&pixel_x, &pixel_y, &pan, &zoom, cnum);

            // The higher the abs of the real value of the complex num, the more green the pixel associated with this value is
            // The higher the abs of the imaginary value of the complex num, the more red the pixel associated with this value is
            set_pixel_color(pixel_x, pixel_y, int(255.0L - 255.0L/(abs(cnum->getReal()*0.75L)+1)), int(255.0L - 255.0L/(abs(cnum->getImaginary()*0.75L)+1)), 0);
        }
    }
    delete cnum;
}

void App::draw_mandelbrot_set(int max_iterations) {
    Complex *cnum = new Complex();
    for (int pixel_y = 0; pixel_y < HEIGHT; pixel_y++) {
        for (int pixel_x = 0; pixel_x < WIDTH; pixel_x++) {
            MdbSetMath::px_pos_to_cnum(&pixel_x, &pixel_y, &pan, &zoom, cnum);
            if (MdbSetMath::is_part_of_mdb_set(cnum, max_iterations)) set_pixel_color(pixel_x, pixel_y, 0, 0, 0);
        }
    }
    delete cnum;
}

void App::update() {
    cnt++;
}

void App::render() {
    set_background();
    draw_mandelbrot_set(MAX_ITERATIONS);
    // Render
    SDL_RenderPresent(renderer);
}

void App::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool App::running() { return is_running; }