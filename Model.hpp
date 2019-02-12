#pragma once

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/Scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

#include "Engine.hpp"

#include "Mesh.hpp"
#include "Actor.hpp"

class Model : public Actor
{
private:
	float rotationAngle;

	std::vector<Texture> loadedTextures;
	std::map<std::string, Mesh> meshes;

	void processNode(aiNode *node, const aiScene *ActorList);
	Mesh processMesh(aiMesh *mesh, const aiScene *ActorList);

	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

public:
	Model(glm::vec3 position, glm::vec3 scale, Material* material);
	~Model();

	Material* material;
	void loadModel(std::string path);

	void setRotation(glm::vec3 rotation, float degree);

	void Render();

	Mesh* findMesh(std::string id);
};
