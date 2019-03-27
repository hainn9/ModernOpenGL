#version 330 core

out vec4 color;

uniform vec4 u_color;

void main(void)
{
    color = u_color;
}
