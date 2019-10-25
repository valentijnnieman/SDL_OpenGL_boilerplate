#pragma once
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <glm/gtc/quaternion.hpp> 

namespace Bodhisattva {
	class Light
	{
	public:
		Light(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
		~Light();
		void Render();

		// Transform
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;
	};

	typedef std::map<std::string, Light*> LightList;
	typedef std::pair<std::string, Light*> NamedLight;
}
