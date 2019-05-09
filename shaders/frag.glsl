#version 430 core

uniform vec3 lightPosition;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform sampler2D MainTexture;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normals;

out vec4 color;

void main()
{
	vec3 lightColor = specularColor;
	// We want unit vectors!
	vec3 normals = normalize(Normals);
	// calculate direction vector between light position and fragment position
	vec3 lightDirection = normalize(lightPosition - FragPos);
	// What's the difference between the normals and the light's direction vector?
	float difference = max(dot(normals, lightDirection), 0.0);
	// Calculate diffuse color
	vec3 diffuse = difference * lightColor;
	vec3 combinedColor = (diffuseColor + diffuse);
	color = vec4(combinedColor, 1.0) * texture(MainTexture, TexCoord);
}
