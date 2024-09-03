#version 460 core
layout(location = 0) in vec2 aPos;
out vec2 TexCoord;

void main() {  
    TexCoord = aPos * 3; // Convert from [-1, 1] to [0, 1]
    gl_Position = vec4(aPos, 0.0, 1.0);
}