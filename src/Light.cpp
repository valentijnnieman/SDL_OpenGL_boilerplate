#include "Light.hpp"

namespace Bodhisattva {
	Light::Light(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		:position(position), rotation(rotation), scale(scale)
	{
	}
	void Light::Render()
	{

	}
	Light::~Light()
	{
	}
}
