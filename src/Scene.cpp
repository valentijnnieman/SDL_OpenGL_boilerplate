#include "Scene.hpp"

namespace Bodhisattva {
	ActorList* Scene::getActors() 
	{ 
		return actors; 
	};
	LightList* Scene::getLights() 
	{ 
		return lights; 
	};
	Camera* Scene::getMainCamera() 
	{ 
		return mainCamera; 
	};
	void Scene::setActors(ActorList* al)
	{ 
		actors = al; 
	};
	void Scene::setLights(LightList* ll) 
	{ 
		lights = ll; 
	};
	void Scene::setMainCamera(Camera* cam) 
	{
		mainCamera = cam;
	}

	void Scene::addLight(NamedLight nLight) 
	{
		lights->insert(nLight);
	}
	void Scene::addActor(NamedActor nActor) 
	{
		actors->insert(nActor);
	}
}



