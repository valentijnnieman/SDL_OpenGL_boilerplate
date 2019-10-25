#pragma once

#include <SDL/SDL.h>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp> 

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp> 

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "Mesh.hpp"

namespace Bodhisattva {
	class Model
	{
	private:
		float rotationAngle;

		std::vector<Texture> loadedTextures;
		std::map<std::string, Mesh> meshes;

		void processNode(aiNode *node, const aiScene *ActorList, bool loadTextures);
		Mesh processMesh(aiMesh *mesh, const aiScene *ActorList, bool loadTextures);

		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

		// Transform
		glm::vec3* position;
		glm::quat* rotation;
		glm::vec3* scale;

		// MVP matrices
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;

	public:
		Model(glm::vec3* position, glm::quat* rotation, glm::vec3* scale, Material* material);
		~Model();

		Material* material;
		void loadModel(std::string path, bool loadTextures=true);

		//void setRotation(glm::vec3 rotation, float degree);

		void Render();

		Mesh* findMesh(std::string id);
		std::map<std::string, Mesh>* getMeshes() { return &meshes; };
	};
}
