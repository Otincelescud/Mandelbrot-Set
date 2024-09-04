#include "app.h"

App::App(const int width, const int height, const int max_iterations) : WIDTH(width), HEIGHT(height), MAX_ITERATIONS(max_iterations)
{}

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
        
        GPU_Graphics::create_shader_program();
        GPU_Graphics::setup_quad();

        cnt = 0;
        is_running = true;
    }
    else {
        is_running = false;
        std::cerr << "Can't initialise SDL2\n";
        return false;
    }

    zoom = 6;
    pan[0] = -3.0; pan[1] = -3.0;
    left_click = false;
    pan_amount[0] = 0; pan_amount[1] = 0;
    zoom_fac = 0;
    return true;
}

void App::handle_events() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        is_running = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEWHEEL:
                zoom_fac = get_zoom_amount(event.wheel.y);
                break;
            case SDL_MOUSEMOTION:
                pan_amount[0] = -get_pan_amount(event.motion.xrel);
                pan_amount[1] = get_pan_amount(event.motion.yrel);
                mouse_pos[0] = event.motion.x;
                mouse_pos[1] = HEIGHT-event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) left_click = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) left_click = false;
                break;
            default:
                break;
        }
    }
}

float App::get_zoom_amount(int scroll_move) {
    return -float(scroll_move)/16;
}

float App::get_pan_amount(int mouse_move) {
    return float(mouse_move)*zoom/HEIGHT;
}

void App::update() {
    // Update variables
    cnt++;

    // Update Pan
    if (left_click) {
        pan[0] += pan_amount[0];
        pan[1] += pan_amount[1];
    }
    pan_amount[0] = 0.0; pan_amount[1] = 0.0;

    // Modify pan in order for screen to zoom in on the cursor

    pan[0] += zoom*float(mouse_pos[0])/WIDTH;
    pan[1] += zoom*float(mouse_pos[1])/HEIGHT;

    zoom += zoom * zoom_fac; 

    // Modify it back to maintain the zoom in point's relative position to the bottom-left corner fo the window

    pan[0] -= zoom*float(mouse_pos[0])/WIDTH;
    pan[1] -= zoom*float(mouse_pos[1])/HEIGHT;

    zoom_fac = 0;

    // Update variables in shader
    GPU_Graphics::set_uniform_vector(pan, "pan");
    GPU_Graphics::set_uniform(zoom, "zoom");
}

void App::render() {
    GPU_Graphics::render();
}

void App::clean() {
    GPU_Graphics::clean();
    SDL_Quit();
}

bool App::running() { return is_running; }