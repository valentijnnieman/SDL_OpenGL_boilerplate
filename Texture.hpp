#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GL/glew.h"
#include <string>

#include "Engine.hpp"

class Texture
{
private:
	SDL_Surface *surface;
	GLuint texture;
	GLint nChannels;
public:
	Texture(std::string filename);
	~Texture();

	std::string type;
	std::string path;

	inline GLuint getTextureId() { return texture; };

	void loadTexture(std::string filename);
};

