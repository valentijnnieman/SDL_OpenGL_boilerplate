#include <SDL.h>
#include "glad/glad.h"
// #include <SDL_OpenGL.h>
#ifdef __APPLE__
#else
// #include <filesystem>
#endif

#include "../src/Engine.hpp"
#include "../src/Actor.hpp"
#include "../src/Scene.hpp"
#include "../src/Model.hpp"
#include "../src/Camera.hpp"
#include "../src/Light.hpp"
#include "../src/Debug.hpp"

int IN_MENU_FLAG = 1;
int IN_GAME_FLAG = 1;

class Cube : public Actor
{
public:
	Cube(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: Actor(position, rotation, scale)
	{
		Debug::Log("Creating material for Cube");
		material = new Material(glm::vec3(1.0), glm::vec3(0.8, 0.8, 0.8), "shaders/vert.glsl", "shaders/frag.glsl");
		Debug::Log("Creating model for Cube");
		model = new Model(&this->position, &this->rotation, &this->scale, material);
		Debug::Log("Loading model for Cube");
		model->loadModel("Models/Demo/Cube.obj");
		Debug::Log("Creating rigidbody for Cube");
		rigidbody = new Rigidbody(1.0, position, new btBoxShape(btVector3(1.0, 1.0, 1.0)));
	};
	~Cube()
	{
		delete material;
		delete model;
	};
};

int main(int argc, char *argv[])
{
	// Setup engine services with defaults
	Engine::initDefault();

	Debug::Log("Boddhisatva!");

	ActorList actors;
	LightList lights;

	Debug::Log("Creating [Actor] cube...");
	Cube cube(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0), glm::vec3(1.0));
	Debug::Log("[Actor] created cube!");

	actors.insert(NamedActor("Cube", &cube));

	Light moonLight = Light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));

	lights.insert(NamedLight("Moonlight", &moonLight));

	Camera cam(glm::vec3(0.0f, 5.0f, 0.0f));

	Debug::Log("Creating scene_01...");
	Scene scene_01 = Scene();
	scene_01.setActors(&actors);
	scene_01.setLights(&lights);
	scene_01.setMainCamera(&cam);

	Engine::setCurrentScene(&scene_01);
	Debug::Log("[scene_01] ready!");

	float xVelocity = 0;
	float zVelocity = 0;

	glm::vec3 oldPosition = cam.position;
	const float moveSpeed = 0.1f;
	const float mouseSpeed = 0.1f;

	float radian = 0.0f;

	SDL_Event menuEvent;

	Debug::Log("Setting current scene to [scene_01]...");
	// Get the current Scene to render
	Scene *currentScene = Engine::getCurrentScene();

	Debug::Log("Ready to render!");
	while (IN_MENU_FLAG)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Iterate over lights
		LightList::iterator light;
		for (light = currentScene->getLights()->begin(); light != currentScene->getLights()->end(); light++)
		{
			light->second->Render();
		}
		// Iterate over Actors in the current ActorList & render them
		ActorList::iterator actor;
		for (actor = currentScene->getActors()->begin(); actor != currentScene->getActors()->end(); actor++)
		{
			actor->second->Render();
		}

		radian += 1.0f;

		SDL_GL_SwapWindow(Engine::getWindow());

		while (SDL_PollEvent(&menuEvent))
		{
			switch (menuEvent.type)
			{
			case SDL_KEYDOWN:
				switch (menuEvent.key.keysym.sym)
				{
				case SDLK_RETURN:
					IN_MENU_FLAG = 0;
					IN_GAME_FLAG = 1;
					break;
				case SDLK_s:
					zVelocity = 1.0f;
					break;
				case SDLK_w:
					zVelocity = -1.0f;
					break;
				case SDLK_a:
					xVelocity = -1.0f;
					break;
				case SDLK_d:
					xVelocity = 1.0f;
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				switch (menuEvent.key.keysym.sym)
				{
				case SDLK_s:
					if (zVelocity > 0)
						zVelocity = 0.0f;
					break;
				case SDLK_w:
					if (zVelocity < 0)
						zVelocity = 0.0f;
					break;
				case SDLK_a:
					if (xVelocity < 0)
						xVelocity = 0.0f;
					break;
				case SDLK_d:
					if (xVelocity > 0)
						xVelocity = 0.0f;
					break;
				case SDLK_q:
					IN_MENU_FLAG = 0;
					IN_GAME_FLAG = 0;
					break;
				default:
					break;
				}
				break;
			case SDL_QUIT:
				IN_MENU_FLAG = 0;
				IN_GAME_FLAG = 0;
				break;
			case SDL_MOUSEMOTION:
				int x = menuEvent.motion.xrel;
				int y = menuEvent.motion.yrel;
				cam.setRotation(glm::vec3(x * mouseSpeed, y * mouseSpeed, 0));
				break;
			}
		}

		oldPosition = oldPosition + zVelocity * moveSpeed * -cam.front;
		oldPosition = oldPosition + xVelocity * moveSpeed * cam.right;

		cam.position = oldPosition;
	}
	//while (IN_GAME_FLAG)
	//{
	//}

	ActorList::iterator it;

	for (it = actors.begin(); it != actors.end(); it++)
	{
		it->second = nullptr;
		delete it->second;
	}

	Engine::shutdown();

	return 0;
}
