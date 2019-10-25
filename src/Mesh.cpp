#include "Debug.hpp"
#include "Mesh.hpp"


namespace Bodhisattva {
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material* material)
		:vertices(vertices), indices(indices), textures(textures), material(material)
	{
		// Generate 1 Vertex Buffer Object, 1 Element Buffer Object, and 1 Vertex Array Object
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		// Bind newly created objects
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Create space for the vertices
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		// Bind Element Buffer Object
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// Set indices to Element Buffer Object
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}

	void Mesh::Render(GLuint* shaderID)
	{
		if (textures.size() > 0)
		{
			// Set the texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[0].getTextureId());

			glUniform1i(glGetUniformLocation(*shaderID, "MainTexture"), GL_TEXTURE0);
		}

		// draw mesh
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		Debug::Log("~Mesh()");
		//glDeleteBuffers(VBO, &VBO);
		//glDeleteVertexArrays(1, &VAO);
	}
}
