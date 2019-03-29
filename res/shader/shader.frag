#version 330 core

out vec4 color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture;

void main(void)
{
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
}
