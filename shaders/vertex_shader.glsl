#version 330 core
layout(location = 0) in vec2 aPos;
out vec2 TexCoord;
uniform vec2 pan;
uniform float zoom;
uniform ivec2 DIMS;
void main() {  
    vec2 tempCoords = (aPos + 1.0) / 2.0; // Convert from [-1, 1] to [0, 1]

    TexCoord = pan + zoom * tempCoords * DIMS;

    gl_Position = vec4(aPos, 0.0, 1.0);
}