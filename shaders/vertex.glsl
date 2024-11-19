#version 330 core

layout (location = 0) in vec3 vpos;
layout (location = 1) in vec2 vtex_cord;

out vec2 tex_cord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(vpos, 1.0f);
    tex_cord    = vtex_cord;
}

