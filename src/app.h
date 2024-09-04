#ifndef App_h
#define App_h

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <fstream>
#include <string>
#include <sstream>
#include "graphics.h"
#include "utils.h"

class App {
public:
    App(const int WIDTH, const int HEIGHT, const int max_iterations);
    ~App();

    bool init(const char *title, int xpos, int ypos, bool fullscreen);

    void handle_events();
    void update();
    void render();
    void clean();

    bool running();

private:
    float get_zoom_amount(int scroll_move);
    float get_pan_amount(int mouse_move);
    float pan_amount[2];
    int mouse_pos[2];
    float zoom_fac;
    bool left_click;
    bool is_running;
    const int WIDTH;
    const int HEIGHT;
    const int MAX_ITERATIONS;
    int cnt;
    float pan[2];
    float zoom;
};

#endif /* App_h */