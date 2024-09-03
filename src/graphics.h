#ifndef GPU_Graphics_h
#define GPU_Graphics_h
#define vertexShaderSource "shaders/vertex_shader.glsl"
#define fragmentShaderSource "shaders/fragment_shader.glsl"

#include "app.h"

class GPU_Graphics {
public:
    static bool init_graphics(const char* w_title, int w_xpos, int w_ypos, const int w_WIDTH, const int w_HEIGHT, int w_flags);
    static void create_shader_program();
    static void setup_quad();
    static void render();
    static void clean();

private:
    static SDL_Window *window;
    static SDL_GLContext gl_context;
    static unsigned int VAO, VBO, shader_program;
    static bool init_GL();
    static bool create_GL_context();
    static bool create_window(const char* w_title, int w_xpos, int w_ypos, const int w_WIDTH, const int w_HEIGHT, int w_flags);
    static unsigned int compile_shader(unsigned int type, const char* source);
};

#endif /* GPU_Graphics_h */