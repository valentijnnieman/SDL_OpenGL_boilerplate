#include "Material.hpp"

Material::Material(glm::vec3 diffuseColor, glm::vec3 specularColor, std::string vertName, std::string fragName)
	: diffuseColor(diffuseColor), specularColor(specularColor), vertexShaderName(vertName), fragmentShaderName(fragName)
{
	Debug::Log("[Material] constructor()");
	// Texture defaults to null
	texture = NULL;
	// create shaders
	Debug::Log("[Material] creating shaders...");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	Debug::Log("[Material] loading vert shader...");
	Debug::Log(vertName.c_str());
	// Load default vertex shader
	std::string vertexSourceString = readFile(vertName.c_str());
	const char *vertexSourceFromFile = vertexSourceString.c_str();

	Debug::Log("[Material] compiling vert shader...");
	glShaderSource(vertexShader, 1, &vertexSourceFromFile, NULL);
	glCompileShader(vertexShader);

	GLint vertShaderIsLoaded;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertShaderIsLoaded);
	if (!vertShaderIsLoaded)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't compile vertex shader: %s", SDL_GetError());
	}

	Debug::Log("[Material] loading frag shader...");
	// Load default fragment shader
	std::string fragmentSourceString = readFile(fragName.c_str());
	const char *fragmentSourceFromFile = fragmentSourceString.c_str();

	Debug::Log("[Material] compiling frag shader...");
	glShaderSource(fragmentShader, 1, &fragmentSourceFromFile, NULL);
	glCompileShader(fragmentShader);

	GLint fragShaderIsLoaded;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragShaderIsLoaded);
	if (!fragShaderIsLoaded)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't compile fragment shader: %s", SDL_GetError());
	}

	Debug::Log("[Material] All shaders loaded!");

	// Link the vertex and fragment shader into a shader program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glBindFragDataLocation(shaderID, 0, "outColor");
	glLinkProgram(shaderID);
	glUseProgram(shaderID);
}
Material::Material(std::string vertName, std::string fragName)
{
	// Texture defaults to null
	texture = NULL;
	// create shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Load default vertex shader
	std::string vertexSourceString = readFile(vertName.c_str());
	const char *vertexSourceFromFile = vertexSourceString.c_str();

	glShaderSource(vertexShader, 1, &vertexSourceFromFile, NULL);
	glCompileShader(vertexShader);

	GLint vertShaderIsLoaded;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertShaderIsLoaded);
	if (!vertShaderIsLoaded)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't compile vertex shader: %s", SDL_GetError());
	}

	// Load default fragment shader
	std::string fragmentSourceString = readFile(fragName.c_str());
	const char *fragmentSourceFromFile = fragmentSourceString.c_str();

	glShaderSource(fragmentShader, 1, &fragmentSourceFromFile, NULL);
	glCompileShader(fragmentShader);

	GLint fragShaderIsLoaded;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragShaderIsLoaded);
	if (!fragShaderIsLoaded)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't compile fragment shader: %s", SDL_GetError());
	}

	// Link the vertex and fragment shader into a shader program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glBindFragDataLocation(shaderID, 0, "outColor");
	glLinkProgram(shaderID);
	glUseProgram(shaderID);
}
void Material::setAttrib()
{
	glUseProgram(shaderID);

	// Set the color of the fragment data
	glUniform3f(glGetUniformLocation(shaderID, "diffuseColor"), diffuseColor.x, diffuseColor.y, diffuseColor.z);
	glUniform3f(glGetUniformLocation(shaderID, "specularColor"), specularColor.x, specularColor.y, specularColor.z);
	// Set the current time
	glUniform1ui(glGetUniformLocation(shaderID, "_Time"), Engine::getTime(SDL_GetTicks()));

	if (texture != nullptr)
	{
		// Set the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureId());

		glUniform1i(glGetUniformLocation(shaderID, "MainTexture"), GL_TEXTURE0);
	}
}

std::string Material::readFile(const char *filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

Material::~Material()
{
	glDeleteProgram(shaderID);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
}
