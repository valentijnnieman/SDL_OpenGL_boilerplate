#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Material.hpp"

namespace Bodhisattva {
	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class Mesh
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		unsigned int VBO, EBO, VAO;
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material* material);
		void Render(GLuint* shaderID);

		Material* material;
		void setMaterial(Material* newMaterial) { material = newMaterial; };
		void setTextures(std::vector<Texture> newTextures) { textures = newTextures; };

		std::vector<Vertex>* getVertices() { return &vertices; };

		~Mesh();
	};
}
