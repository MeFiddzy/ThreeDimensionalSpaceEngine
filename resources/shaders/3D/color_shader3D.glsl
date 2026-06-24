#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_MVP;
uniform mat4 u_model;

out vec3 v_worldPos;

void main() {
    vec4 worldPos = u_model * vec4(position, 1.0);
    v_worldPos = worldPos.xyz;
    gl_Position = u_MVP * vec4(position, 1.0);
}

#shader fragment
#version 330 core

in vec3 v_worldPos;
out vec4 color;

uniform vec4 u_color;
uniform vec3 u_lightDir;

void main() {
    vec3 normal = normalize(cross(dFdx(v_worldPos), dFdy(v_worldPos)));
    float diffuse = max(dot(normal, normalize(u_lightDir)), 0.0);
    float ambient = 0.15;
    float lighting = ambient + (1.0 - ambient) * diffuse;
    color = vec4(u_color.rgb * lighting, u_color.a);
}