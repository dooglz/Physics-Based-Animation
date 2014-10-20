#include <stdio.h>
#include <cstring>
#include <iostream>

#include "SDL_platform.h"
#include "Utilities.h"
#include "OGL_Renderer.h"

#include <glew/glew.h>
#include <sdl/SDL.h>
//#include <sdl\SDL_opengl.h>
#define DEFAULT_HEIGHT 720
#define DEFAULT_WIDTH 1280


void SDLVersionInfo()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("Compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void GlewInfo()
{
	printf("----------------------------------------------------------------\n");
	printf("OpenGL Info\n");
	
	printf("Glew Version: %s\n", glewGetString(GLEW_VERSION));
	printf("     Version: %s\n", glGetString(GL_VERSION));
	printf("      Vendor: %s\n", glGetString(GL_VENDOR));
	printf("    Renderer: %s\n", glGetString(GL_RENDERER));
	printf("     Shading: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("----------------------------------------------------------------\n");
}

SDL_assert_state CustomAssertionHandler(const SDL_assert_data* data, void* userdata)
{
	Engine::SDL::SDL_Platform::CheckGL();
	Engine::SDL::SDL_Platform::CheckSDL();
	SDL_AssertionHandler defaultHandler = SDL_GetDefaultAssertionHandler();
	return defaultHandler(data, userdata);
}

namespace Engine{
	unsigned short Platform::_screenWidth;
	unsigned short Platform::_screenHeight;

	namespace SDL{

		SDL_Window*   SDL_Platform::_window;
		SDL_GLContext SDL_Platform::_gContext;


		void SDL_Platform::CheckGL(){
			GLenum err;
			while ((err = glGetError()) != GL_NO_ERROR) {
				printf("An OGL error has occured: %i\n", err);
			}
		}


		void SDL_Platform::CheckSDL(){
			const char* err = SDL_GetError();
			if (strlen(err) != 0){
				printf("SDL error: %s\n", err);
				SDL_ClearError();
			}
		}

		SDL_Platform::SDL_Platform()
		{
			printf("SDL Platform Loading\n");
			SDLVersionInfo();
			//Initialize SDL
			SDL_SetAssertionHandler(CustomAssertionHandler, NULL);
			ASSERT((SDL_Init(SDL_INIT_VIDEO) >= 0));

		
		}
		void SDL_Platform::Init()
		{
			Renderer = new COGL_Renderer();
		}
		void SDL_Platform::createwindow()
		{
			_window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			ASSERT(_window != NULL);
			_gContext = SDL_GL_CreateContext(_window);
			ASSERT(_gContext != NULL);

			GLenum err = glewInit();
			CheckGL();
			GlewInfo();

			if (GLEW_VERSION_4_4){
				_glverMaj = 4;
				_glverMin = 4;
			}else if (GLEW_VERSION_4_3){
				_glverMaj = 4;
				_glverMin = 3;
			}else if (GLEW_VERSION_4_0){
				_glverMaj = 4;
				_glverMin = 0;
			}else if (GLEW_VERSION_3_3){
				_glverMaj = 3;
				_glverMin = 3;
			}else if (GLEW_VERSION_3_0){
				_glverMaj = 3;
				_glverMin = 0;
			}else{
				printf("Unknown GL Version!\n");
			}

			printf("Using OGL version: %i.%i\n", _glverMaj, _glverMin);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, _glverMaj);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, _glverMin);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			_screenHeight = DEFAULT_HEIGHT;
			_screenWidth = DEFAULT_WIDTH;
			printf("Display Resolution: %i x %i\n", _screenWidth, _screenHeight);
			//Vsync
			ASSERT(SDL_GL_SetSwapInterval(1) >= 0);
		}

		void SDL_Platform::Shutdown()
		{
			SDL_GL_DeleteContext(_gContext);
			SDL_DestroyWindow(_window);
			SDL_Quit();
		}
	}
}
