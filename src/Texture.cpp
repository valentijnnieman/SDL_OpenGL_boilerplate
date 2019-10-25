#include "Texture.hpp"
#include "Engine.hpp"
#include "glad/glad.h"

namespace Bodhisattva {
	Texture::Texture(std::string filename)
	{
		loadTexture(filename);
	}


	Texture::~Texture()
	{
	}

	int Texture::getTextureId() 
	{ 
		return texture; 
	};

	void Texture::loadTexture(std::string filename)
	{
		path = Engine::getTextureDirectory() + filename;
		SDL_Surface *surface = IMG_Load(path.c_str());

		// Generate OpenGl texture
		glGenTextures(1, &texture);

		int Mode = GL_RGB;
		if (surface)
		{
			if (surface->format->BytesPerPixel == 4)
			{
				Mode = GL_RGBA;
			}

			//// Bind texture & set parameters
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Generate texture using an SDL_Surface
			glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);
			//glGenerateMipmap(GL_TEXTURE_2D);
			// Free surface
			SDL_FreeSurface(surface);
		}
	}
}
