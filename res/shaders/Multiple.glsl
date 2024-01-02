#shader vertex
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 u_Color;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in float texInd;

uniform mat4 u_MVP;

out vec4 v_Color;
out float v_TexInd;
out vec2 v_TexCoord;

void main() {
    vec4 newPosition = u_MVP * vec4(position, 1.0f);
    gl_Position = vec4(newPosition.x, newPosition.y, newPosition.z, newPosition.w);
    v_Color = u_Color;
    v_TexInd = texInd;
    v_TexCoord = texCoord;
}

#shader fragment
#version 460 core

in vec4 v_Color;
in float v_TexInd;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

out vec4 color;

void main() {
    int ind = int(v_TexInd);
    vec4 texColor = texture(u_Texture, v_TexCoord);
    if (ind == 0)
    {
        color = v_Color;
    } else
    {
        color = texColor;
    }
}