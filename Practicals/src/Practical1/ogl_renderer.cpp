#include "glew/glew.h"
#include "utilities.h"
#include "helpermath.h" // Vector3, Matrix4, and Quaternion
#include "ogl_renderer.h"
#include <sdl\SDL_opengl.h>
#include <gl\glu.h>
#include "sdl/SDL.h"
#include <stdio.h>


#define RADPERDEG 0.0174533
extern void CheckGL();



void COGL_Renderer::PrepForRender()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearDepth(1.0f);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
	//glViewport(0,0,1920,1080);

	CheckGL();
}


void GLInfo()
{
	printf("---------------- OpenGL Info -----------------------------------\n");
	printf("    Version: %s\n", glGetString(GL_VERSION));
	printf("     Vendor: %s\n", glGetString(GL_VENDOR));
	printf("   Renderer: %s\n", glGetString(GL_RENDERER));
	printf("    Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("----------------------------------------------------------------\n");
}

void COGL_Renderer::Clear()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CheckGL();
}

Vector3 COGL_Renderer::GetMousePosition2Dto3D()
{

	return Vector3(0, 0, 0);
}

void COGL_Renderer::FinishRender(){
	SDL_GL_SwapWindow(_window);
}

void COGL_Renderer::InitDisplay()
{
	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
	//Create an ogl window
	_window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	//Create context
	SDL_GLContext _gContext = SDL_GL_CreateContext(_window);
	SDL_assert(_gContext != NULL);
	GLInfo();

	//Initialize GLEW, do we even need it?
	glewExperimental = GL_TRUE;
	SDL_assert(glewInit() == GLEW_OK);
	//Glewinit always throws an error, due to that experimental flag, just ignore it.
	glGetError();

	//Use Vsync
	SDL_assert(SDL_GL_SetSwapInterval(1) >= 0);
	
}