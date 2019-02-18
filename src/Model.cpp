#include "Model.hpp"

Model::Model(glm::vec3 position, glm::vec3 scale, Material* mat)
	:Actor(position, scale)
{
	material = mat;

	// Calculate model
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	rotationAngle = 0.0f;

	glUniformMatrix4fv(glGetUniformLocation(material->shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	// Set the attributes on the shaders of the material
	material->setAttrib();
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *ActorList = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); 

	if(!ActorList || ActorList->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !ActorList->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(ActorList->mRootNode, ActorList);
}

void Model::processNode(aiNode * node, const aiScene * ActorList)
{
	// Go through all of node's meshes 
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
		std::cout << node->mName.C_Str() << std::endl;
        aiMesh *mesh = ActorList->mMeshes[node->mMeshes[i]]; 
		meshes.insert({ mesh->mName.C_Str(), processMesh(mesh, ActorList)});
    }

	// Go through all of node's children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
		// Recursively process node for all of this node's children
        processNode(node->mChildren[i], ActorList);
    }
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * ActorList)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// texture coordinates
		if(mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			// Only get first set of texturecoords for now
			vec.x = mesh->mTextureCoords[0][i].x; 
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		vertices.push_back(vertex);
	}
	// Get indices from loaded model from it's faces
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// process materials
	aiMaterial* material = ActorList->mMaterials[mesh->mMaterialIndex];    

	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	return Mesh(vertices, indices, textures);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
std::vector<Texture> Model:: loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for(unsigned int j = 0; j < loadedTextures.size(); j++)
		{
			if(std::strcmp(loadedTextures[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}
		if(!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture(str.C_Str());
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			loadedTextures.push_back(texture); 
		}
	}
	return textures;
}

void Model::setRotation(glm::vec3 rotation, float degree)
{
	rotation = glm::normalize(rotation);
	rotationAngle = glm::radians(degree);
}

void Model::Render()
{
	material->setAttrib();

	// Calculate model
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);

	model = glm::scale(model, scale);

	model = glm::rotate(model, rotationAngle, rotation);

	glUniformMatrix4fv(glGetUniformLocation(material->shaderID, "model"), 1, GL_FALSE, glm::value_ptr(model));

	Camera* cam = Engine::getCurrentCamera();

	glm::vec3 f = cam->front;

	// Set the view of the vertex data
	view = glm::lookAt(
		cam->position, 
		cam->position + cam->front,
		cam->up
	);

	glUniformMatrix4fv(glGetUniformLocation(material->shaderID, "view"), 1, GL_FALSE, glm::value_ptr(view));

	// Set projection of the vertex data
	projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1F, 1000.0f);
	glUniformMatrix4fv(glGetUniformLocation(material->shaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// Render meshes
	std::map<std::string, Mesh>::iterator it;

	for (it = meshes.begin(); it != meshes.end(); it++) 
	{
        it->second.Render(&material->shaderID);
	}
}
Mesh* Model::findMesh(std::string id) 
{ 
	std::map<std::string, Mesh>::iterator it;
	it = meshes.find(id);
	if (it == meshes.end()) 
	{
		return NULL;
	}

	return &it->second;
}
Model::~Model()
{
	material = nullptr;
	delete material;
}

