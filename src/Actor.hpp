#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Actor
{
public:
	Actor(glm::vec3 position, glm::vec3 scale)
		:position(position), scale(scale) {};
	~Actor();

	// Transform
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	// Basis/direction vectors
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	// MVP matrices
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	virtual void Render();
};

