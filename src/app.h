#ifndef App_h
#define App_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include "mdb_set_math.h"
#include "graphics.h"
#include "utils.h"

class App {
public:
    App(const int WIDTH, const int HEIGHT, const int max_iterations);
    ~App();

    bool init(const char *title, int xpos, int ypos, bool fullscreen);

    void handle_events();
    void set_pixel_color(SDL_Surface* surface, int x, int y, int r, int g, int b);
    void set_background();
    void update();
    void render();
    void clean();

    bool running();

private:
    bool is_running;
    const int WIDTH;
    const int HEIGHT;
    const int MAX_ITERATIONS;
    int cnt;
    Complex pan;
    long double zoom;
};

#endif /* App_h */