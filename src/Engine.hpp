#pragma once
#include <SDL.h>
#include <string>
#include <stdlib.h>
#include <map>
#include "glad/glad.h"
#include "btBulletDynamicsCommon.h"

#include "Scene.hpp"
#include "Debug.hpp"

/*
	Services
*/

class EngineTextureService
{
private:
	std::string textureDir;

public:
	void setTextureDir(std::string dir) { textureDir = dir; };
	std::string getTextureDir() { return textureDir; };
};

class EngineClockService
{
private:
	Uint32 startTime;

public:
	EngineClockService(Uint32 start) { startTime = start; };
	Uint32 getTime(Uint32 currentTime) { return currentTime - startTime; };
};

class EngineSceneService
{
private:
	Scene *currentScene;
	Camera *currentCamera;

public:
	Scene *getCurrentScene() { return currentScene; };
	Camera *getCurrentCamera() { return currentScene->getMainCamera(); };

	void setCurrentScene(Scene *scene) { currentScene = scene; };
	void setCurrentCamera(Camera *camera) { currentScene->setMainCamera(camera); };
};

class EngineRandomService
{
public:
	EngineRandomService()
	{
		// Init seed for random number generator
		srand(time(NULL));
	}
	int randomInt(int min, int max) { return rand() % max + min; };
};

/*
	Engine class
*/
class Engine
{
private:
	inline static EngineTextureService *textureService;
	inline static EngineClockService *clockService;
	inline static EngineSceneService *sceneService;
	inline static EngineRandomService *randomService;

	inline static SDL_Window *window;
	inline static SDL_GLContext ctx;

	inline static btDefaultCollisionConfiguration *collisionConfiguration;
	inline static btCollisionDispatcher *dispatcher;
	inline static btBroadphaseInterface *broadphase;
	inline static btSequentialImpulseConstraintSolver *solver;
	inline static btDiscreteDynamicsWorld *dynamicsWorld;

public:
	~Engine()
	{
		textureService = nullptr;
		delete textureService;

		clockService = nullptr;
		delete clockService;

		sceneService = nullptr;
		delete sceneService;

		randomService = nullptr;
		delete randomService;

		delete collisionConfiguration;
		delete dispatcher;
		delete broadphase;
		delete solver;
		delete dynamicsWorld;
	};
	// Initializers
	static void initDefault()
	{
		Debug::Log("Setting up SDL...");
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
			SDL_Quit();
		}

		SDL_DisplayMode dpmode;
		SDL_GetCurrentDisplayMode(0, &dpmode);
		SDL_GL_SetAttribute(
			SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		window = SDL_CreateWindow(
			"OpenGL Test",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			dpmode.w,
			dpmode.h,
			SDL_WINDOW_OPENGL);

		ctx = SDL_GL_CreateContext(window);
		Debug::Log("[SDL] Done!");

		Debug::Log("Setting up GLAD...");
		int gladInitRes = gladLoadGL();
		if (!gladInitRes)
		{
			fprintf(stderr, "Unable to initialize glad\n");
			SDL_Quit();
		}
		Debug::Log("[GLAD] Done!");

		printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

		SDL_GL_SetSwapInterval(1);
		glEnable(GL_DEPTH_TEST);
		SDL_SetRelativeMouseMode(SDL_TRUE);

		EngineTextureService *ts = new EngineTextureService();
		EngineClockService *cs = new EngineClockService(SDL_GetTicks());
		EngineSceneService *ss = new EngineSceneService();
		EngineRandomService *rs = new EngineRandomService();

		Engine::provideTextureService(ts);
		Engine::setTextureDirectory("Textures/");
		Engine::provideClockService(cs);
		Engine::provideSceneService(ss);
		Engine::provideRandomService(rs);

		Debug::Log("Setting up Bullet...");
		// Setup Bullet physics engine
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		broadphase = new btDbvtBroadphase();
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -10, 0));
		Debug::Log("[Bullet] Done!");
	};

	// Destroyers
	static void shutdown()
	{
		SDL_GL_DeleteContext(ctx);
		SDL_DestroyWindow(window);
		SDL_Quit();
	};

	// Providers
	inline static void provideTextureService(EngineTextureService *service) { textureService = service; };
	inline static void provideClockService(EngineClockService *service) { clockService = service; };
	inline static void provideSceneService(EngineSceneService *service) { sceneService = service; };
	inline static void provideRandomService(EngineRandomService *service) { randomService = service; };

	// Getters
	static std::string getTextureDirectory() { return textureService->getTextureDir(); };
	static Uint32 getTime(Uint32 currentTime) { return clockService->getTime(currentTime); };
	static int RandomInt(int min, int max) { return randomService->randomInt(min, max); };
	static Scene *getCurrentScene() { return sceneService->getCurrentScene(); };
	static Camera *getCurrentCamera() { return sceneService->getCurrentCamera(); };
	static SDL_Window *getWindow() { return window; };
	static SDL_GLContext *getContext() { return &ctx; };
	static btDiscreteDynamicsWorld *getWorld() { return dynamicsWorld; };

	// Setters
	static void setTextureDirectory(std::string textureDirectory) { textureService->setTextureDir(textureDirectory); };
	static void setCurrentScene(Scene *scene) { sceneService->setCurrentScene(scene); };
	static void setCurrentCamera(Camera *camera) { sceneService->setCurrentCamera(camera); };

	// Debug
};
