#version 330 core

uniform vec3 lambertColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normals;

out vec4 color;

void main()
{
	vec3 lightColor = vec3(1.0,1.0,1.0);
	vec3 lightPosition = vec3(0.0, 10.0, 0.0);
	// We want unit vectors!
	vec3 normals = normalize(Normals);
	// calculate direction vector between light position and fragment position
	vec3 lightDirection = normalize(lightPosition - FragPos);
	// What's the difference between the normals and the light's direction vector?
	float difference = max(dot(normals, lightDirection), 0.0);
	// Calculate diffuse color
	vec3 diffuse = difference * lightColor;
	vec3 ambientColor = vec3(0.1, 0.1, 0.1);
	vec3 combinedColor = (ambientColor + diffuse);
	color = vec4(combinedColor, 1.0);
}
