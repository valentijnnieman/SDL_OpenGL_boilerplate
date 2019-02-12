#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	float yaw;
	float pitch;
public:
	Camera(glm::vec3 position);
	~Camera();

	// Transform
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	// Basis/direction vectors
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	void setRotation(glm::vec3 newRotation);
	void Render();
};

