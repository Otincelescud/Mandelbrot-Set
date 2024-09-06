#include "app.h"

App::App(const int width, const int height, const int max_iterations) : WIDTH(width), HEIGHT(height), MAX_ITERATIONS(max_iterations)
{}

App::~App() {}

bool App::init(const char *title, int xpos, int ypos, bool fullscreen) {
    int flags = 0;
    DIMENSIONS[0] = WIDTH, DIMENSIONS[1] = HEIGHT;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        if (fullscreen) {
            flags = SDL_WINDOW_FULLSCREEN;
            
            SDL_DisplayMode displayMode;

            // Get the display mode of the primary display (index 0)
            if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
                SDL_Log("SDL_GetCurrentDisplayMode Error: %s", SDL_GetError());
                SDL_Quit();
                return false;
            }
            DIMENSIONS[0] = displayMode.w; DIMENSIONS[1] = displayMode.h;
        }

        if (!GPU_Graphics::init_graphics(title, xpos, ypos, DIMENSIONS[0], DIMENSIONS[1], flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) {
            SDL_Quit();
            is_running = false;
            return false;
        }
        

        GPU_Graphics::create_shader_program();
        GPU_Graphics::setup_quad();
        glUseProgram(GPU_Graphics::get_shader_program());

        cnt = 0;
        is_running = true;

        GPU_Graphics::set_uniform(MAX_ITERATIONS, "MAX_ITERATIONS");
        GPU_Graphics::set_uniform_vector(DIMENSIONS, "DIMS");
    }
    else {
        is_running = false;
        std::cerr << "Can't initialise SDL2\n";
        return false;
    }

    zoom = 6.0/DIMENSIONS[1];
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
                pan_amount[0] += -get_pan_amount(event.motion.xrel);
                pan_amount[1] += get_pan_amount(event.motion.yrel);
                mouse_pos[0] = event.motion.x;
                mouse_pos[1] = DIMENSIONS[1]-event.motion.y;
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
    return float(mouse_move)*zoom;
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

    pan[0] += get_pan_amount(mouse_pos[0]);
    pan[1] += get_pan_amount(mouse_pos[1]);

    zoom += zoom * zoom_fac; 

    // Modify it back to maintain the zoom in point's relative position to the bottom-left corner fo the window

    pan[0] -= get_pan_amount(mouse_pos[0]);
    pan[1] -= get_pan_amount(mouse_pos[1]);

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