#pragma once
#include <SDL/SDL.h>
#include <string>
#include <stdlib.h>
#include <map>
#include "glad/glad.h"
#include "Bullet/btBulletDynamicsCommon.h"

#include "Scene.hpp"
#include "Debug.hpp"

/*
	Services
*/

namespace Bodhisattva {
	class EngineTextureService
	{
	private:
		std::string textureDir;

	public:
		void setTextureDir(std::string dir);
		std::string getTextureDir();
	};

	class EngineClockService
	{
	private:
		Uint32 startTime;

	public:
		EngineClockService(Uint32 start);
		Uint32 getTime(Uint32 currentTime);
	};

	class EngineSceneService
	{
	private:
		Scene *currentScene;
		Camera *currentCamera;

	public:
		Scene *getCurrentScene();
		Camera *getCurrentCamera();

		void setCurrentScene(Scene *scene);
		void setCurrentCamera(Camera *camera);
	};

	class EngineRandomService
	{
	public:
		EngineRandomService();
		int randomInt(int min, int max);
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

		inline static GLDebugDrawer debugDrawer;

	public:
		~Engine();
		// Initializers
		static void initDefault();

		// Destroyers
		static void shutdown();

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
}
