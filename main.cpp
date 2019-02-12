#pragma once
#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <filesystem>

#include "Engine.hpp"
#include "Scene.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Light.hpp"

int IN_MENU_FLAG = 1;
int IN_GAME_FLAG = 1;

int main(int, char **)
{
	// Setup engine services with defaults
	Engine::initDefault();

	SDL_Window *window;
	SDL_GLContext ctx;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	SDL_DisplayMode dpmode;
	SDL_GetCurrentDisplayMode(0, &dpmode);

	window = SDL_CreateWindow(
		"OpenGL Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		dpmode.w/2,
		dpmode.h/2,
		SDL_WINDOW_OPENGL
	);

	ctx = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	glewInit();

	SDL_GL_SetAttribute
	(
		SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE
	);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	ActorList actors;
	ActorList lights;

	Texture waterTexture = Texture("water4.jpg");
	Material waterMaterial = Material(glm::vec3(0.2, 0.8, 1.0), "shaders/water-vert.glsl", "shaders/water-frag.glsl");
	waterMaterial.texture = &waterTexture;

	// textures for the boat model are gotten through it's .mtl file
	Material boatMaterial = Material(glm::vec3(0.8, 0.8, 0.8), "shaders/vert.glsl", "shaders/frag.glsl");

	Material distandIslandMaterial = Material(glm::vec3(0.8, 0.8, 0.8), "shaders/vert.glsl", "shaders/frag.glsl");

	Model boat = Model(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.2), &boatMaterial);
	boat.loadModel("Models/Demo/OldBoat.obj");

	Model lighthouse = Model(glm::vec3(0.0, 0.0, 150.0), glm::vec3(3.0), &boatMaterial);
	lighthouse.loadModel("Models/Demo/lighthouse.obj");

	Model island = Model(glm::vec3(0.0, -1.0, 150.0), glm::vec3(0.1), &distandIslandMaterial);
	island.loadModel("Models/Demo/island.obj");

	Model ocean = Model(glm::vec3(0.0), glm::vec3(1.0), &waterMaterial);
	ocean.loadModel("Models/Demo/ocean.obj");
	Model ocean_2 = Model(glm::vec3(100.0, 0.0, 0.0), glm::vec3(1.0), &waterMaterial);
	ocean_2.loadModel("Models/Demo/ocean.obj");
	Model ocean_3 = Model(glm::vec3(0.0, 0.0, 100.0), glm::vec3(1.0), &waterMaterial);
	ocean_3.loadModel("Models/Demo/ocean.obj");
	Model ocean_4 = Model(glm::vec3(100.0, 0.0, 100.0), glm::vec3(1.0), &waterMaterial);
	ocean_4.loadModel("Models/Demo/ocean.obj");
	Model ocean_5 = Model(glm::vec3(-100.0, 0.0, 0.0), glm::vec3(1.0), &waterMaterial);
	ocean_5.loadModel("Models/Demo/ocean.obj");
	Model ocean_6 = Model(glm::vec3(-100.0, 0.0, 100.0), glm::vec3(1.0), &waterMaterial);
	ocean_6.loadModel("Models/Demo/ocean.obj");
	Model ocean_7 = Model(glm::vec3(100.0, 0.0, 200.0), glm::vec3(1.0), &waterMaterial);
	ocean_7.loadModel("Models/Demo/ocean.obj");
	Model ocean_8 = Model(glm::vec3(0.0, 0.0, 200.0), glm::vec3(1.0), &waterMaterial);
	ocean_8.loadModel("Models/Demo/ocean.obj");
	Model ocean_9 = Model(glm::vec3(-100.0, 0.0, 200.0), glm::vec3(1.0), &waterMaterial);
	ocean_9.loadModel("Models/Demo/ocean.obj");
	
	actors.insert(NamedActor("Ocean", &ocean));
	actors.insert(NamedActor("Ocean_2", &ocean_2));
	actors.insert(NamedActor("Ocean_3", &ocean_3));
	actors.insert(NamedActor("Ocean_4", &ocean_4));
	actors.insert(NamedActor("Ocean_5", &ocean_5));
	actors.insert(NamedActor("Ocean_6", &ocean_6));
	actors.insert(NamedActor("Ocean_7", &ocean_7));
	actors.insert(NamedActor("Ocean_8", &ocean_8));
	actors.insert(NamedActor("Ocean_9", &ocean_9));

	actors.insert(NamedActor("Boat", &boat));
	//actors.insert(NamedActor("Lighthouse", &lighthouse));
	actors.insert(NamedActor("Island", &island));

	Light moonLight = Light(glm::vec3(0.0f, 40.0f, 0.0f), glm::vec3(0.0f));

	lights.insert(NamedActor("Moonlight", &moonLight));

	Camera cam(glm::vec3(0.0f, 5.0f, 0.0f));

	Scene scene_01 = Scene();
	scene_01.setActors(&actors);
	scene_01.setLights(&lights);
	scene_01.setMainCamera(&cam);

	Engine::setCurrentScene(&scene_01);

	float xVelocity = 0;
	float zVelocity = 0;

	glm::vec3 oldPosition = cam.position;
	const float moveSpeed = 0.5f;

	float radian = 0.0f;

	SDL_Event menuEvent;

	// Get the current Scene to render
	Scene* currentScene = Engine::getCurrentScene();

	while (IN_MENU_FLAG)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Iterate over lights
		ActorList::iterator light;
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

		SDL_GL_SwapWindow(window);

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
					if(zVelocity > 0)
						zVelocity = 0.0f;
					break;
				case SDLK_w:
					if(zVelocity < 0)
						zVelocity = 0.0f;
					break;
				case SDLK_a:
					if(xVelocity < 0)
						xVelocity = 0.0f;
					break;
				case SDLK_d:
					if(xVelocity > 0)
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
				cam.setRotation(glm::vec3(x, y, 0));
				break;
			}
		}

		//oldPosition.x += xVelocity * moveSpeed;
		//oldPosition.z += zVelocity * moveSpeed;

		oldPosition = oldPosition + zVelocity * moveSpeed * -cam.front;
		oldPosition = oldPosition + xVelocity * moveSpeed * cam.right;

		cam.position = oldPosition;
	}
	//while (IN_GAME_FLAG)
	//{
	//}

	SDL_GL_DeleteContext(ctx);
	ActorList::iterator it;

	for (it = actors.begin(); it != actors.end(); it++)
	{
		it->second = nullptr;
		delete it->second;
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
