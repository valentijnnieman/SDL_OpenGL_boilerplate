#pragma once
#include "Actor.hpp"
#include "Light.hpp"
#include "Camera.hpp"
#include <map>
#include <string>

namespace Bodhisattva {
	class Scene
	{
	private:
		ActorList* actors;
		LightList* lights;
		// Only one camera for now
		Camera* mainCamera;

	public:
		// Getters
		ActorList* getActors();
		LightList* getLights();
		Camera* getMainCamera();

		// Setters
		void setActors(ActorList* al);
		void setLights(LightList* ll);
		void setMainCamera(Camera* cam);
		//Adders
		void addLight(NamedLight nLight);
		void addActor(NamedActor nActor);
	};
}
