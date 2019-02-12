#pragma once

#include "Actor.hpp"
#include "Camera.hpp"

#ifndef ENGINE_TYPES
#define ENGINE_TYPES
typedef std::map<std::string, Actor*> ActorList;
typedef std::pair<std::string, Actor*> NamedActor;
#endif

class Scene
{
private:
	ActorList* actors;
	ActorList* lights;
	// Only one camera for now
	Camera* mainCamera;

public:
	// Getters
	ActorList* getActors() { return actors; };
	ActorList* getLights() { return lights; };
	Camera* getMainCamera() { return mainCamera; };

	// Setters
	void setActors(ActorList* al) { actors = al; };
	void setLights(ActorList* al) { lights = al; };
	void setMainCamera(Camera* cam) {
		mainCamera = cam;
	}
	
	//Adders
	void addLight(NamedActor nActor) {
		lights->insert(nActor);
	}
	void addActor(NamedActor nActor) {
		actors->insert(nActor);
	}
};

