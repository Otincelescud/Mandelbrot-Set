#include "graphics.h"

SDL_Window *GPU_Graphics::window = nullptr;
SDL_GLContext GPU_Graphics::gl_context = nullptr;
unsigned int GPU_Graphics::VAO, GPU_Graphics::VBO, GPU_Graphics::shader_program;

bool GPU_Graphics::create_window(const char* w_title, int w_xpos, int w_ypos, const int w_WIDTH, const int w_HEIGHT, int w_flags) {
    window = SDL_CreateWindow(w_title,
                                w_xpos, w_ypos,
                                w_WIDTH, w_HEIGHT,
                                w_flags);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    return true;
}

bool GPU_Graphics::create_GL_context() {
    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        SDL_Log("Failed to create OpenGL context: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return false;
    }
    return true;
}

bool GPU_Graphics::init_GL() {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_Log("Failed to initialize OpenGL context with glad");
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        return false;
    }
    return true;
}

bool GPU_Graphics::init_graphics(const char* w_title, int w_xpos, int w_ypos, const int w_WIDTH, const int w_HEIGHT, int w_flags) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (create_window(w_title, w_xpos, w_ypos, w_WIDTH, w_HEIGHT, w_flags) && create_GL_context() && !SDL_GL_MakeCurrent(window, gl_context) && init_GL()) return true;
    SDL_Log("Couldn't initialize graphics");

    return false;
}

void GPU_Graphics::render() {
    glClearColor(0.5f, 0.1f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shader_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    SDL_GL_SwapWindow(window);
}

void GPU_Graphics::clean() {
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_program);
}


unsigned int GPU_Graphics::compile_shader(unsigned int type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        SDL_Log("ERROR::SHADER::COMPILATION_FAILED\n%s", infoLog);
    }
    return shader;
}

void GPU_Graphics::create_shader_program() {
    std::string vertex_code = Utils::read_file_source(vertexShaderSource);
    std::string fragment_code = Utils::read_file_source(fragmentShaderSource);

    unsigned int vertexShader = compile_shader(GL_VERTEX_SHADER, vertex_code.c_str());
    unsigned int fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragment_code.c_str());
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertexShader);
    glAttachShader(shader_program, fragmentShader);
    glLinkProgram(shader_program);
    int success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        SDL_Log("ERROR::PROGRAM::LINKING_FAILED\n%s", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void GPU_Graphics::setup_quad() {
    float vertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GPU_Graphics::set_uniform(double var, const char* label) {
    GLenum uniformLoc =  glGetUniformLocation(shader_program, label);
    glUniform1d(uniformLoc, var);
}

void GPU_Graphics::set_uniform_vector(double *ptr, const char* label) {
    GLenum uniformLoc =  glGetUniformLocation(shader_program, label);
    glUniform2dv(uniformLoc, 1, ptr);
}

void GPU_Graphics::set_uniform(int var, const char* label) {
    GLenum uniformLoc =  glGetUniformLocation(shader_program, label);
    glUniform1i(uniformLoc, var);
}

void GPU_Graphics::set_uniform_vector(int *ptr, const char* label) {
    GLenum uniformLoc =  glGetUniformLocation(shader_program, label);
    glUniform2iv(uniformLoc, 1, ptr);
}

void GPU_Graphics::set_uniform(float var, const char* label) {
    GLenum uniformLoc =  glGetUniformLocation(shader_program, label);
    glUniform1f(uniformLoc, var);
}

void GPU_Graphics::set_uniform_vector(float *ptr, const char* label) {
    GLenum uniformLoc =  glGetUniformLocation(shader_program, label);
    glUniform2fv(uniformLoc, 1, ptr);
}