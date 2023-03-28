#version 330 core

in vec2 tex_coord;

out vec4 out_color;

uniform vec4 ucolor;

void main() {
    out_color = ucolor; // vec4(1.0, 0.0, 0.0, 1.0);
}