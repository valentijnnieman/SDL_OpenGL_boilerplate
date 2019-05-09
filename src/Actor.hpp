#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "btBulletDynamicsCommon.h"
#include "Physics/Rigidbody.hpp"
#include "Model.hpp"

class Actor
{
private:
public:
	Actor(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	Actor(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Rigidbody *rb);
	~Actor();

	Rigidbody *rigidbody;
	Material *material;
	Model *model;

	// Transform
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	// Basis/direction vectors
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	btRigidBody *getRigidbody() { return rigidbody->rigidbody; };

	virtual void Render();
};
