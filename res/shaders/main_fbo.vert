#version 330 core
layout (location = 0) in vec2 apos;

out vec2 tex_coord;

void main() {
    tex_coord = apos+vec2(0.5, 0.5);
    gl_Position = vec4(apos * 2.0, 0.0, 1.0);
}