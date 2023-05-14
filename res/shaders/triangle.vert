#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

out vec3 color;

void main() {
    color = aColor;
    gl_Position = uProj * uView * uModel * vec4(aPos, 0.0, 1.0);
}
