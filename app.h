#ifndef App_h
#define App_h

#include "SDL2/SDL.h"

class App {
public:
    App(const int WIDTH, const int HEIGHT);
    ~App();

    void init(const char *title, int xpos, int ypos, bool fullscreen);

    void handle_events();
    void set_pixel_color(int x, int y, int r, int g, int b);
    void update();
    void render();
    void clean();

    bool running();

private:
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    const int WIDTH;
    const int HEIGHT;
    int cnt;
};

#endif /* App_h */