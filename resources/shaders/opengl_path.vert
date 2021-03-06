#version 330

uniform mat4 model_view_proj;

in vec2 in_pos2d;
in float in_height;

void main() {
    gl_Position = model_view_proj * vec4(in_pos2d, in_height, 1.0);
}