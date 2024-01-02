#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 u_Color;

uniform mat4 u_Proj;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec4 v_Color;

void main() {
    vec4 newPosition = u_Proj * u_View * u_Model * position;
    gl_Position = newPosition;
    v_Color = u_Color;
}

#shader fragment
#version 460 core

in vec4 v_Color;

out vec4 color;

void main() {
    color = v_Color;
}