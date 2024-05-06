#ifdef __WIN32
#include <windows.h>
#endif

#include "app.h"

#define WIDTH 600
#define HEIGHT 600
#define FPS 60
#define FRAME_DELAY 1000 / FPS

App *app = nullptr;

Uint32 frame_start;
int frame_time;

void start_app() {
    app = new App(WIDTH, HEIGHT);

    app->init("The Mandelbrot Set", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

    while (app->running()) {

        frame_start = SDL_GetTicks();

        app->handle_events();
        app->update();
        app->render();
    }

    frame_time = SDL_GetTicks() - frame_start;
    if (frame_time < FRAME_DELAY) SDL_Delay(FRAME_DELAY - frame_time);

    app->clean();
}

/*#ifdef __WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    start_app();
    return 0;
}*/
#ifdef __linux
int main(int argc, char *argv[]) {
    start_app();
    return 0;
}
#endif