#include "Engine.hpp"
#undef main

int IN_MENU_FLAG = 1;
int IN_GAME_FLAG = 1;

using namespace Bodhisattva;

class Cube : public Actor
{
public:
	Cube(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		: Actor(position, rotation, scale)
	{
		material = new Material(glm::vec3(0.2, 0.4, 0.4), glm::vec3(0.2, 0.45, 0.45), "shaders/vert.glsl", "shaders/color-frag.glsl");
		model = new Model(&this->position, &this->rotation, &this->scale, material);
		model->loadModel("Models/Demo/Cube.obj", false);
		rigidbody = new Rigidbody(100.0, position, new btBoxShape(btVector3(1.0, 1.0, 1.0)));
	};
	~Cube()
	{
		delete material;
		delete model;
	};
};

class Sphere : public Actor
{
public:
	Sphere(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		: Actor(position, rotation, scale)
	{
		material = new Material(glm::vec3(0.2, 0.5, 0.4), glm::vec3(0.1, 0.4, 0.8), "shaders/vert.glsl", "shaders/color-frag.glsl");
		model = new Model(&this->position, &this->rotation, &this->scale, material);
		model->loadModel("Models/Demo/Sphere.obj", false);
		rigidbody = new Rigidbody(100.0, position, new btSphereShape(1.0f));
	};
	~Sphere()
	{
		delete material;
		delete model;
	};
};

class Plane : public Actor
{
public:
	Plane(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		: Actor(position, rotation, scale)
	{
		material = new Material(glm::vec3(0.2, 0.5, 0.4), glm::vec3(0.3, 0.1, 0.2), "shaders/vert.glsl", "shaders/color-frag.glsl");
		model = new Model(&this->position, &this->rotation, &this->scale, material);
		model->loadModel("Models/Demo/Plane.obj", false);
		rigidbody = new Rigidbody(0.0, position, new btBoxShape(btVector3(100.0, 0.001, 100.0)));
	};
	~Plane()
	{
		delete material;
		delete model;
	};
};

class Lamp : public Actor
{
public:
	Lamp(glm::vec3 position, glm::quat rotation, glm::vec3 scale)
		: Actor(position, rotation, scale)
	{
		material = new Material(glm::vec3(1.0), glm::vec3(1.0), "shaders/vert.glsl", "shaders/color-frag.glsl");
		model = new Model(&this->position, &this->rotation, &this->scale, material);
		model->loadModel("Models/Demo/Cube.obj", false);
		light = new Light(position, rotation, scale);
	};
	~Lamp()
	{
		delete material;
		delete model;
	};
};

int main(int argc, char *argv[])
{
	// Setup engine services with defaults
	Engine::initDefault();

	ActorList actors;
	LightList lights;

	Cube cube(glm::vec3(30.0, 2.0, 10.0), glm::vec3(0.0), glm::vec3(1.0));

	Lamp lamp_01 = Lamp(glm::vec3(10.0f, 20.0f, 20.0f), glm::vec3(0.0f), glm::vec3(1.0f));
	lights.insert(NamedLight("Moonlight", lamp_01.light));

	actors.insert(NamedActor("Cube", &cube));

	actors.insert(NamedActor("sphere_01", new Cube(glm::vec3(4.0, 15.0, 0.0), glm::vec3(0.0), glm::vec3(1.0))));
	actors.insert(NamedActor("sphere_02", new Sphere(glm::vec3(2.0, 12.0, 0.0), glm::vec3(0.0), glm::vec3(1.0))));
	actors.insert(NamedActor("sphere_04", new Cube(glm::vec3(-6.0, 11.0, 0.0), glm::vec3(0.0), glm::vec3(1.0))));
	actors.insert(NamedActor("sphere_05", new Sphere(glm::vec3(5.0, 15.0, 5.0), glm::vec3(0.0), glm::vec3(1.0))));
	actors.insert(NamedActor("sphere_06", new Cube(glm::vec3(2.0, 12.0, 5.0), glm::vec3(0.0), glm::vec3(1.0))));
	actors.insert(NamedActor("sphere_07", new Sphere(glm::vec3(-3.0, 13.0, 5.0), glm::vec3(0.0), glm::vec3(1.0))));
	actors.insert(NamedActor("sphere_08", new Cube(glm::vec3(-6.0, 11.0, 5.0), glm::vec3(0.0), glm::vec3(1.0))));
	actors.insert(NamedActor("lamp_01", &lamp_01));

	actors.insert(NamedActor("Plane", new Plane(glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0), glm::vec3(10.0))));

	Camera cam(glm::vec3(0.0f, 40.5f, 40.0f));
	cam.setRotation(glm::vec3(0.0, 45.0f, 0.0f));

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

	while (IN_GAME_FLAG)
	{
		Engine::renderCurrentScene();

		radian += 1.0f;

		while (SDL_PollEvent(&menuEvent))
		{
			switch (menuEvent.type)
			{
			case SDL_KEYDOWN:
				switch (menuEvent.key.keysym.sym)
				{
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
				case SDLK_ESCAPE:
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

		Engine::update();
	}
	ActorList::iterator it;

	for (it = actors.begin(); it != actors.end(); it++)
	{
		it->second = nullptr;
		delete it->second;
	}

	Engine::shutdown();

	return 0;
}
