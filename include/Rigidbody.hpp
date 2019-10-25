#pragma once
#include "Bullet/btBulletDynamicsCommon.h"
#include <glm/glm.hpp>

namespace Bodhisattva {
	class Rigidbody
	{
	public:
		Rigidbody(float mass, glm::vec3 position, btCollisionShape *col);
		~Rigidbody();

		btRigidBody *rigidbody;
		btCollisionShape *collider;
	};
}
