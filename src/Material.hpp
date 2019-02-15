#pragma once

#include <SDL.h>
#include <gl\glew.h>
#include <gl\glu.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>
#include "Texture.hpp"
#include "Light.hpp"

class Material
{
private:
	glm::mat4 model;
	glm::mat4 view;

	glm::vec3 color;

	GLuint vertexShader;

	GLuint fragmentShader;

public:
	Material(glm::vec3 color, std::string vertName, std::string fragName);
	~Material();

	GLuint shaderID;
	Texture* texture;

	std::string readFile(const char *filePath);

	void setAttrib();
};

