#version 330 core

in vec2 tex_coord;
out vec4 out_color;

uniform sampler2D utex;

void main() {
    vec4 c = texture(utex, tex_coord);
    out_color = c;
}