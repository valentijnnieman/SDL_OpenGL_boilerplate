#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "glad/glad.h"
#include <SDL/SDL_opengl.h>
#include <string>

namespace Bodhisattva {
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

		int getTextureId();

		void loadTexture(std::string filename);
	};
}
