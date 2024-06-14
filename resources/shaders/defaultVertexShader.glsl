#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color_for_vertex_shader;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec4 color_for_fragment_shader;

void main() {
    gl_Position = proj * view * model * vec4(position, 1.0);
    color_for_fragment_shader = color_for_vertex_shader;
}