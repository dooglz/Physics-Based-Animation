#pragma once
#include "renderer.h"
#include "sdl/SDL.h"

class Vector3;

class COGL_Renderer :public CRenderer
{
public:

	Vector3 GetMousePosition2Dto3D();

	void PrepForRender();
	void FinishRender();
	void InitDisplay();
	void InitSurfaces();
	void Clear();
	SDL_Window* _window;
	SDL_GLContext _glcontext;
};