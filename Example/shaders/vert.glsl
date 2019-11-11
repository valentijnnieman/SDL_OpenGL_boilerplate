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
	TexCoord = v_TexCoord;
	FragPos = vec3(model * vec4(position, 1.0));
	Normals = mat3(transpose(inverse(model))) * normals;
	// Transform position into world space for frag shader
	gl_Position = projection * view * vec4(FragPos, 1.0);
}
