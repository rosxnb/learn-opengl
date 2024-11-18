#version 330 core

in  vec2 tex_cord;
out vec4 frag_color;

uniform sampler2D texture1, texture2;

void main()
{
    frag_color = mix(texture(texture1, tex_cord),
                     texture(texture2, tex_cord), 0.5);
}
