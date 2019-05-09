#version 430 core
#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 v_TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform uint _Time;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normals;

void main()
{
	vec3 newPosition = position;
//	newPosition.y = newPosition.y + normals.y * sin(gl_VertexID *  normals.y * _Time / 10000) * 1.0;

	float wavelength = 10.0;
	float amplitude = 0.6;
	float speed = 0.001;

	float k = 2 * M_PI / wavelength;
//	newPosition.y += amplitude * sin(k* newPosition.y * normals.y - speed * _Time);
	newPosition.y += sin(newPosition.y * _Time);

	vec2 tc = v_TexCoord;
	TexCoord = tc;
	Normals = normals;
	// Transform position into world space for frag shader
	FragPos = vec3(model * vec4(position, 1.0));
	gl_Position = projection * view * model * vec4(newPosition, 1.0);
}
