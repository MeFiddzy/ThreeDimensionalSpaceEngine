#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec2 xyPos;

void main() {
    xyPos = vec2(position.x, position.y);
    gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 xyPos;

uniform float u_coef;

void main() {
    color = vec4(u_coef * xyPos.x, 0, u_coef * xyPos.y, 1.0);
}