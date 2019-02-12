#version 330 core

uniform vec3 lambertColor;

out vec4 color;

void main()
{
	color = vec4(lambertColor, 1.0);
}
