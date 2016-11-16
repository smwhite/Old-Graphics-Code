#version 330

in vec4 color;

out vec4 frag_color;

uniform sampler2D gSampler;

void main()
{
    frag_color = color;
}
          
