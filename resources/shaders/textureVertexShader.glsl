#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_for_vertex_shader;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 proj;

uniform mat4 camMatrix;

out vec2 texture_for_fragment_shader;

void main() {
    gl_Position = camMatrix * vec4(position, 1.0);
    //gl_Position = model * view * proj * vec4(position, 1.0);
    texture_for_fragment_shader = texture_for_vertex_shader;
}