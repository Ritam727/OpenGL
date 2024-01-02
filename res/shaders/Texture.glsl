#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texInd;

out vec2 v_TexCoord;
out float v_TexInd;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * position;
    v_TexCoord = texCoord;
    v_TexInd = texInd;
}

#shader fragment
#version 460 core

out vec4 color;

uniform sampler2D u_Texture[2];

in vec2 v_TexCoord;
in float v_TexInd;

void main() {
    int ind = int(v_TexInd);
    vec4 texColor = texture(u_Texture[ind], v_TexCoord);
    color = texColor;
}