#version 330 core
in vec4 color_for_fragment_shader;
out vec4 color_for_blending;
void main() {
        color_for_blending = vec4(color_for_fragment_shader);
}