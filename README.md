# Bodhisattva

![](https://freepngimg.com/download/temp/31696-7-buddha-temple-clipart_64x64.ico)

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

In main.cpp, a small demo scene is set up. There is basic lighting (Phong) and basic shading, as well as first person camera control. You can press escape to quit.

## How can I use this?

Clone the repo, and install submodules by runnin `git submodule update --init --recursive`.

Besides VS project files included, there's also a CMake file that you can use to build the project for your system.
You'd need to have the dependencies listed above installed (on mac, `brew install sdl2`, `brew install assimp`, `brew install sdl2_image`, `brew install glm` should do it. `glad` is already bundled and should load the correct OpenGL dependencies for you) and then run `cmake CMakeLists.txt`.
Check out the demo scene set up in main.cpp - it handles basic creation of a Scene, Lights and Camera's, as well as Material creation, Texture loading, and Model loading.
