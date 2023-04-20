#version 330 core
layout (location = 0) in vec2 apos;

uniform mat4 umodel;
uniform mat4 uview;
uniform mat4 uproj;

out vec2 tex_coord;

void main() {
    vec4 p = uproj * uview * umodel * vec4(apos * 2.0, 0.0, 1.0);
    tex_coord = apos+vec2(0.5, 0.5);
    gl_Position = p;
}