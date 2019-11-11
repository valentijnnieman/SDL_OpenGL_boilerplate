#include "Engine.hpp"
#include "Scene.hpp"
#include "Debug.hpp"
#include "SDL.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <map>
#include "glad/glad.h"
#include "Bullet/btBulletDynamicsCommon.h"

namespace Bodhisattva {
	void EngineTextureService::setTextureDir(std::string dir)
	{
		textureDir = dir;
	};
	std::string EngineTextureService::getTextureDir()
	{
		return textureDir;
	};

	Scene* EngineSceneService::getCurrentScene() {
		return currentScene;
	};
	Camera* EngineSceneService::getCurrentCamera()
	{
		return currentScene->getMainCamera();
	};
	void EngineSceneService::setCurrentScene(Scene *scene)
	{
		currentScene = scene;
	};
	void EngineSceneService::setCurrentCamera(Camera *camera)
	{
		currentScene->setMainCamera(camera);
	};

	EngineClockService::EngineClockService(Uint32 start)
	{
		startTime = start;
	};
	Uint32 EngineClockService::getTime(Uint32 currentTime)
	{
		return currentTime - startTime;
	};

	EngineRandomService::EngineRandomService()
	{
		// Init seed for random number generator
		srand(time(NULL));
	}
	int EngineRandomService::randomInt(int min, int max) { return rand() % max + min; };

	void Engine::initDefault() {
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
			dpmode.w / 3.f ,
			dpmode.h / 3.f,
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
		debugDrawer.setDebugMode(btIDebugDraw::DBG_DrawWireframe);
		dynamicsWorld->setDebugDrawer(&debugDrawer);
		Debug::Log("[Bullet] Done!");
	};

	void Engine::renderCurrentScene() 
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Iterate over lights
		LightList::iterator light;
		for (light = sceneService->getCurrentScene()->getLights()->begin(); light != sceneService->getCurrentScene()->getLights()->end(); light++)
		{
			light->second->Render();
		}
		// Iterate over Actors in the current ActorList & render them
		ActorList::iterator actor;
		for (actor = sceneService->getCurrentScene()->getActors()->begin(); actor != sceneService->getCurrentScene()->getActors()->end(); actor++)
		{
			actor->second->Render();
		}

		SDL_GL_SwapWindow(getWindow());
	}

	void Engine::update() 
	{
		btClock capTimer = btClock();
		float avgFPS = frameCount / (SDL_GetTicks() / 1000.f );
		Debug::Log(avgFPS);

		frameCount++;
		//If frame finished early
		int frameTicks = capTimer.getTimeMilliseconds();
		Engine::getWorld()->stepSimulation(maxTicksPerFrame - frameTicks, 1);
		if(frameTicks < maxTicksPerFrame)
		{
			//Wait remaining time
			SDL_Delay(maxTicksPerFrame - frameTicks);
		}
	}

	Engine::~Engine()
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

	void Engine::shutdown()
	{
		SDL_GL_DeleteContext(ctx);
		SDL_DestroyWindow(window);
		SDL_Quit();
	};
}
