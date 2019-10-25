#pragma once

#include <SDL/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"

#include <fstream>
#include <string>
#include "Texture.hpp"

namespace Bodhisattva {
	class Material
	{
	private:
		glm::mat4 model;
		glm::mat4 view;

		glm::vec3 diffuseColor;
		glm::vec3 specularColor;

		GLuint vertexShader;

		GLuint fragmentShader;

	public:
		Material(std::string vertName, std::string fragName);
		Material(glm::vec3 diffuseColor, glm::vec3 specularColor, std::string vertName, std::string fragName);
		~Material();

		GLuint shaderID;
		Texture* texture;

		std::string vertexShaderName;
		std::string fragmentShaderName;

		std::string readFile(const char *filePath);

		void setAttrib();
	};
}
