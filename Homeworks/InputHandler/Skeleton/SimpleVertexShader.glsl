#version 330 core
  
layout (location = 0) in vec3 position;

uniform mat4 MVP;

void main()
{
	//ORder = VEC * Model * View * Proj
    gl_Position = vec4(position.x, position.y, position.z, 1.0) * MVP;
}