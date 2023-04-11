#version 330 core
layout (location = 0) in vec2 apos;

uniform vec2 usize;
uniform vec2 uoffset;

out vec2 tex_coord;

void main() {
    vec4 p = vec4(apos * 2.0, 0.0, 1.0);
    p.xy *= usize;
    p.xy += uoffset;

    tex_coord = apos+vec2(0.5, 0.5);
    gl_Position = p;
}