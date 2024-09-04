#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform float zoom;
void main() {
    vec4 backgroundColor = vec4(0.2, 0.0, 0.6, 1.0);
    FragColor = vec4(0.0, 0.0, 0.0, 1.0);

    if (length(TexCoord) > 2) FragColor = backgroundColor;
    else {
        vec2 zn = vec2(0.0, 0.0);
        for (int i = 0; i < 1000 && length(zn) <= 2; i++) {
            zn = vec2(zn.x*zn.x-zn.y*zn.y, 2*zn.x*zn.y) + TexCoord;
        }

        if (length(zn) > 2) FragColor = backgroundColor;
    }
}