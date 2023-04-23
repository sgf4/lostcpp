#version 330 core
layout (location = 0) in vec2 apos;

uniform mat3 umodel;
uniform vec2 uwsize;

out vec2 tex_coord;

void main() {
    vec4 p = vec4(umodel * vec3(apos * 2.0, 1.0) * vec3(1.0, 1.0, -1.0), 1.0);
    tex_coord = apos+vec2(0.5, 0.5);
    gl_Position = p;
}