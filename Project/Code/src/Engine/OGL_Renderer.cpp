#include "OGL_Renderer.h"
#include "SDL_platform.h"
#include "Maths.h"
#include "Mesh.h"
#include "sdl/SDL.h"
#include "glew/glew.h"

namespace Engine{
	namespace SDL{
		float f = 0.0f;
		
		void COGL_Renderer::clearSurface()
		{
			f += 0.001;
			glClearColor(sin(f) , 0.5f, 0.5f, 1.f);
			SDL_Platform::CheckGL();

			//SDL_Delay( 16 );

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			SDL_Platform::CheckGL();
		}

		COGL_Renderer::COGL_Renderer()
		{

		}

		void COGL_Renderer::renderMesh(Mesh* msh, Matrix4 mvp)
		{

		}

		void COGL_Renderer::PrepFrame()
		{

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			glClearDepth(1.0f);
			glViewport(0, 0, SDL_Platform::GetSreenWidth(), SDL_Platform::GetSreenHeight());

			// Cull triangles which normal is not towards the camera
			//glEnable(GL_CULL_FACE);
			//glViewport(0,0,1920,1080);

			SDL_Platform::CheckGL();
			clearSurface();
		}

		void COGL_Renderer::PostRender()
		{
			SDL_GL_SwapWindow(SDL_Platform::GetWindow());
		}
	}
}