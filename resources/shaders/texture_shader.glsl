#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 u_MVP;

out vec2 v_texCoord;

void main() {
    v_texCoord = texCoord;
    gl_Position = u_MVP * position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform sampler2D u_textureSlot;

void main() {
    vec4 texColor = texture(u_textureSlot, v_texCoord);
    //color = vec4(v_texCoord, .5, .5f);
    color = texColor;
}