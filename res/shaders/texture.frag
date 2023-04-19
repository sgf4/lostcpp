#version 330 core

in vec2 tex_coord;
out vec4 out_color;

uniform vec2 utex_offset;
uniform vec2 utex_size;
uniform vec4 ucolor;
uniform sampler2D utex;

void main() {
    vec4 c = texture(utex, tex_coord/utex_size+utex_offset);
    out_color = c * ucolor;
}