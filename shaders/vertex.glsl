#version 330 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec2 vtex_cord;
out vec2 tex_cord;

void main()
{
    gl_Position = vec4(vpos, 1.0);
    tex_cord    = vtex_cord;
}

