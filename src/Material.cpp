#include "Material.hpp"

Material::Material(glm::vec3 color, std::string vertName, std::string fragName)
	:color(color)
{
	// Texture defaults to null
	texture = NULL;
	// create shaders
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Load default vertex shader
	std::string vertexSourceString = readFile(vertName.c_str());
	const char* vertexSourceFromFile = vertexSourceString.c_str();

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
	const char* fragmentSourceFromFile = fragmentSourceString.c_str();

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
	glUniform3f(glGetUniformLocation(shaderID, "lambertColor"), color.x, color.y, color.z);
	// Set the current time
	glUniform1ui(glGetUniformLocation(shaderID, "_Time"), Engine::getTime(SDL_GetTicks()));
	// Get the current scene's lights
	if (Engine::getCurrentScene() != nullptr)
	{
		ActorList* currentLights = Engine::getCurrentScene()->getLights();
		Light* currentLight = (Light*)currentLights->begin()->second;
		// Set the light position (singular for now - get the currentLights' first light)
		glUniform3f(glGetUniformLocation(shaderID, "lightPosition"), currentLight->position.x, currentLight->position.y, currentLight->position.z);
	}

	if (texture != nullptr) 
	{
		// Set the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureId());

		glUniform1i(glGetUniformLocation(shaderID, "MainTexture"), GL_TEXTURE0);
	}
}

std::string Material::readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    std::string line = "";
    while(!fileStream.eof()) {
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
