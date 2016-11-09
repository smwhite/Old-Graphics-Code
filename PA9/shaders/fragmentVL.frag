#version 330

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_tex_coord;
in vec2 tex_coord;

out vec4 frag_color;

uniform sampler2D gSampler;

void main()
{
    frag_color = texture2D(gSampler, tex_coord.xy);
}
          
