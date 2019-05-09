#version 430 core

uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 lightPosition;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normals;

out vec4 color;

void main()
{
	vec3 lightColor = specularColor * 1.5;
	// We want unit vectors!
	vec3 normals = normalize(Normals);
	// calculate direction vector between light position and fragment position
	vec3 lightDirection = normalize(lightPosition - FragPos);
	// What's the difference between the normals and the light's direction vector?
	float difference = max(dot(normals, lightDirection), 0.0);
	// Calculate diffuse color
	vec3 diffuse;
	if(difference > 0.9)
	{
		color = vec4((lightColor * diffuseColor) * 4.0, 1.0);
	}
	else if(difference > 0.5)
	{
		color = vec4((lightColor * diffuseColor) * 3.0, 1.0);
	}
	else if(difference > 0.25)
	{
		color = vec4((lightColor * diffuseColor) * 2.0, 1.0);
	}
	else
	{
		color = vec4((lightColor *diffuseColor)* 1.0, 1.0);
	}
//	vec3 diffuse = difference * lightColor;
//	vec3 combinedColor = diffuseColor + diffuse;
//	color = vec4(combinedColor, 1.0);
}
