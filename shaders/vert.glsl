#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normals;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	TexCoord = v_TexCoord;
	Normals = normals;
	// Transform position into world space for frag shader
	FragPos = vec3(projection * vec4(position, 1.0));
}
