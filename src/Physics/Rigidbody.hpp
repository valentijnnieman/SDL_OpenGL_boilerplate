#pragma once
#include "btBulletDynamicsCommon.h"
#include <glm/glm.hpp>

class Rigidbody
{
public:
	Rigidbody(float mass, glm::vec3 position, btCollisionShape *col);
	~Rigidbody();

	btRigidBody *rigidbody;
	btCollisionShape *collider;
};
