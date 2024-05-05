#ifndef App_h
#define App_h

#include "SDL2/SDL.h"

class App {
public:
    App();
    ~App();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handle_events();
    void update();
    void render();
    void clean();

    bool running();

private:
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int cnt;
};

#endif /* App_h */