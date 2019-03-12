#pragma once

#include <map>
#include <string>
//#include "Actor.hpp"
#include "Camera.hpp"

class Actor;
class Light;

typedef std::map<std::string, Actor*> ActorList;
typedef std::pair<std::string, Actor*> NamedActor;
typedef std::map<std::string, Light*> LightList;
typedef std::pair<std::string, Light*> NamedLight;

class Scene
{
private:
	ActorList* actors;
	LightList* lights;
	// Only one camera for now
	Camera* mainCamera;

public:
	// Getters
	ActorList* getActors() { return actors; };
	LightList* getLights() { return lights; };
	Camera* getMainCamera() { return mainCamera; };

	// Setters
	void setActors(ActorList* al) { actors = al; };
	void setLights(LightList* ll) { lights = ll; };
	void setMainCamera(Camera* cam) {
		mainCamera = cam;
	}
	
	//Adders
	void addLight(NamedLight nLight) {
		lights->insert(nLight);
	}
	void addActor(NamedActor nActor) {
		actors->insert(nActor);
	}
};

