# SDL & OpenGL boilerplate

## Yes, another boilerplate!
Hello! This is my boilerplate (I'm calling it a boilerplate but I guess one could call it an engine too) of SDL and OpenGL code.
It is a work in progress, and if you are looking for a fully fledged boilerplate that is ready to develop the best looking games, this probably isn't it (yet!). However, I'm hoping this is a good starting point for those new to both libraries!

## What does it use?
Other than the SDL2 framework and OpenGL, this uses:
- Assimp for importing .obj models
- GLM for vectors, matrices, etc
- SDL_Image for loading textures

## Demo scene
![Demo gif](demo.gif?raw=true "Demo")

In main.cpp, a small demo scene is set up. Credits go to Herminio Nieves for the Small_Island model, and glDev on Turbosquid.com for the [Old rowboad model](https://www.turbosquid.com/FullPreview/Index.cfm/ID/675083). There is basic lighting (Phong) and basic water shading, as well as first person camera control. You can press 'q' to quit.

## How can I use this?
Check out the demo scene set up in main.cpp - it handles basic creation of a Scene, Lights and Camera's, as well as Material creation, Texture loading, and Model loading. 
