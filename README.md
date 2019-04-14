# Bodhisattva

## A C++ game engine to-be
Hello! This is my C++ game engine I'm writing out in the open, to make games with and hopefully inspire others to make games and perhaps game engines themselves.

It is a work in progress, and if you are looking for a fully fledged engine that is ready to develop the best looking games, this probably isn't it.

## What does it use?
Other than the SDL2 framework and OpenGL, this uses:
- GLAD for handling OpenGL functions
- Assimp for importing .obj models
- GLM for vectors, matrices, etc
- SDL_Image for loading textures

## Demo scene
![Demo gif](demo.gif?raw=true "Demo")

In main.cpp, a small demo scene is set up. Credits go to Herminio Nieves for the Small_Island model, and glDev on Turbosquid.com for the [Old rowboad model](https://www.turbosquid.com/FullPreview/Index.cfm/ID/675083). There is basic lighting (Phong) and basic water shading, as well as first person camera control. You can press 'q' to quit.

## How can I use this?
Besides VS project files included, there's also a CMake file that you can use to build the project for your system.
You'd need to have the dependencies listed above installed (on mac, `brew install sdl2`, `brew install assimp`, `brew install sdl2_image`, `brew install glm` should do it. `glad` is already bundled and should load the correct OpenGL dependencies for you) and then run `cmake CMakeLists.txt`.
Check out the demo scene set up in main.cpp - it handles basic creation of a Scene, Lights and Camera's, as well as Material creation, Texture loading, and Model loading.
