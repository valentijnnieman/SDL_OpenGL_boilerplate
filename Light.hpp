#pragma once
#include "Actor.hpp"

class Light : public Actor
{
public:
	Light(glm::vec3 position, glm::vec3 scale);
	~Light();
	void Render();
};

