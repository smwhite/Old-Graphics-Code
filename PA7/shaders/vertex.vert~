#version 330

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_tex_coord;

out vec2 tex_coord;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix; 


void main()
{
	vec4 v = vec4(v_position, 1.0); 
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * v; 
    tex_coord = v_tex_coord;
}
          
