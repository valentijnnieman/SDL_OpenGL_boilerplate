#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~Light();
	void Render();

	// Transform
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};

