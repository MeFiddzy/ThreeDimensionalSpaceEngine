#version 330 core

out vec4 color;

in vec2 fragPos;

void main() {
     color = vec4(fragPos.y * 0.5, fragPos.x, fragPos.x - fragPos.y * 2, 1.0);
}