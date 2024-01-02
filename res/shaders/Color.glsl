#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 u_Color;

uniform mat4 u_MVP;

out vec4 v_Color;

void main() {
    gl_Position = u_MVP * position;
    v_Color = u_Color;
}

#shader fragment
#version 460 core

in vec4 v_Color;

out vec4 color;

uniform vec4 u_Color;

void main() {
    color = v_Color + u_Color;
}