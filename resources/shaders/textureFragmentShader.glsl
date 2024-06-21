#version 330 core
in vec2 texture_for_fragment_shader;

uniform sampler2D tex0;

out vec4 color_for_blending;

void main() {
        color_for_blending = texture(tex0, texture_for_fragment_shader);
}