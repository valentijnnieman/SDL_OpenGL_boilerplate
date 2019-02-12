#include "Camera.hpp"

Camera::Camera(glm::vec3 position)
	:position(position)
{
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);

	yaw = front.x;
	pitch = front.y;
}

void Camera::Render()
{
	//ActorList::iterator it;

	//ActorList* currentActorList = Engine::getCurrentActorList();

	//for (it = currentActorList->begin(); it != currentActorList->end(); it++) 
	//{
	//	it->second->Render();
	//}
}

void Camera::setRotation(glm::vec3 newRotation)
{
	float xoffset = newRotation.x;
    float yoffset = newRotation.y; 

	float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;
	pitch = std::clamp(pitch, -89.0f, 89.0f);

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = -sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(newFront);
	// Created vec3 below symbolizes "up" in world coordinates
	right = glm::normalize(glm::cross(front, glm::vec3(0.0, 1.0, 0.0)));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}
