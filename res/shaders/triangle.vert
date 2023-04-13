#version 330 core
layout (location = 0) in vec2 apos;
layout (location = 1) in vec3 acolor;

uniform mat4 umodel;
uniform mat4 uview;
uniform mat4 uproj;

out vec3 color;

void main() {
    color = acolor;
    gl_Position = uproj * uview * umodel * vec4(apos, 0.0, 1.0);
}