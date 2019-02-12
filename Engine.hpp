#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include <map>

#include "Scene.hpp"

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
	Scene* currentScene;
	Camera* currentCamera;

public:
	Scene* getCurrentScene() { return currentScene; };
	Camera* getCurrentCamera() { return currentScene->getMainCamera(); };

	void setCurrentScene(Scene* scene) { currentScene = scene; };
	void setCurrentCamera(Camera* camera) { currentScene->setMainCamera(camera); };
};

/* 
	Engine class
*/
class Engine
{
private:
	inline static EngineTextureService* textureService;
	inline static EngineClockService* clockService;
	inline static EngineSceneService* sceneService;

public:
	~Engine() 
	{
		textureService = nullptr;
		delete textureService;

		clockService = nullptr;
		delete clockService;

		sceneService = nullptr;
		delete sceneService;
	};
	// Initializers
	static void initDefault() {
		EngineTextureService* ts = new EngineTextureService();
		EngineClockService* cs = new EngineClockService(SDL_GetTicks());
		EngineSceneService* ss = new EngineSceneService();
		Engine::provideTextureService(ts);
		Engine::setTextureDirectory("Textures/");
		Engine::provideClockService(cs);
		Engine::provideSceneService(ss);
	};

	// Providers
	inline static void provideTextureService(EngineTextureService* service) { textureService = service; };
	inline static void provideClockService(EngineClockService* service) { clockService = service; };
	inline static void provideSceneService(EngineSceneService* service) { sceneService = service; };

	// Getters
	static std::string getTextureDirectory() { return textureService->getTextureDir(); };
	static Uint32 getTime(Uint32 currentTime) { return clockService->getTime(currentTime); };
	static Scene* getCurrentScene() { return sceneService->getCurrentScene(); };
	static Camera* getCurrentCamera() { return sceneService->getCurrentCamera(); };

	// Setters
	static void setTextureDirectory(std::string textureDirectory) { textureService->setTextureDir(textureDirectory); };
	static void setCurrentScene(Scene* scene) { sceneService->setCurrentScene(scene); };
	static void setCurrentCamera(Camera* camera) { sceneService->setCurrentCamera(camera); };

	// Debug
	template<class msg>
	static void Log(msg msg) { std::cout << msg << std::endl; }
};
