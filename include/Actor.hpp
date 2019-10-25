#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Bullet/btBulletDynamicsCommon.h"
#include "Rigidbody.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include <map>
#include <string>

namespace Bodhisattva {
	class Actor
	{
	private:
	public:
		Actor(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
		Actor(glm::vec3 position, glm::quat rotation, glm::vec3 scale, Rigidbody *rb);
		~Actor();

		Rigidbody *rigidbody;
		Material *material;
		Model *model;
		Light *light;

		// Transform
		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rotation;

		// Basis/direction vectors
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;

		btRigidBody *getRigidbody() { return rigidbody->rigidbody; };

		virtual void Render();
	};

	typedef std::map<std::string, Actor*> ActorList;
	typedef std::pair<std::string, Actor*> NamedActor;
}
