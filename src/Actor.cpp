#include "Actor.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Debug.hpp"

namespace Bodhisattva {
	Actor::Actor(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		: position(position), rotation(rotation), scale(scale)
	{
		// default static rigidbody (0 mass, no collider)
		rigidbody = new Rigidbody(0.0, position, new btBoxShape(btVector3(0, 0, 0)));
	};
	Actor::Actor(glm::vec3 position, glm::quat rotation, glm::vec3 scale, Rigidbody *rb)
		: position(position), rotation(rotation), scale(scale), rigidbody(rb)
	{
		Debug::Log("[Actor] constructor()");
	};

	Actor::~Actor()
	{
		delete rigidbody;
	}

	void Actor::Render()
	{
		// Update transform based on Rigidbody
		btTransform trans;
		getRigidbody()->getMotionState()->getWorldTransform(trans);
		position = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
		rotation = glm::quat(trans.getRotation().w(), trans.getRotation().x(), trans.getRotation().y(), trans.getRotation().z());

		// Render the Model
		if (model != nullptr)
		{
			model->Render();
		}
	}
}
