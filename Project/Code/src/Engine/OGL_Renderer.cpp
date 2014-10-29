#include "OGL_Renderer.h"
#include "SDL_platform.h"
#include "Maths.h"
#include "Mesh.h"
#include "sdl/SDL.h"
#include "glew/glew.h"
#include <glm/gtc/type_ptr.hpp>
#include "OGL_ShaderProgram.h"
#include "OGL_FragmentShader.h"
#include "OGL_VertexShader.h"

namespace Engine{
	namespace OGL{
		float f = 0.0f;

		OGL::OGL_ShaderProgram* COGL_Renderer::_defaultProgram;

		void COGL_Renderer::clearSurface()
		{
			f += 0.001f;
			glClearColor(sin(f) , 0.5f, 0.5f, 1.f);
			SDL::SDL_Platform::CheckGL();
			//SDL_Delay( 16 );

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			SDL::SDL_Platform::CheckGL();
		}

		COGL_Renderer::COGL_Renderer()
		{

		}

		void COGL_Renderer::renderMesh(Mesh* msh, Matrix4 mvp)
		{
			ASSERT(msh->program != nullptr);
			glUseProgram(msh->program->getID());
			SDL::SDL_Platform::CheckGL();

			//get shader input indexes
			GLint mvpIn = glGetUniformLocation(msh->program->getID(), "MVP");
			SDL::SDL_Platform::CheckGL();

			//Send MVP
			Matrix4 projMatrix = Perspective((float)(60.0f*(M_PI / 180.0f)), (16.0f / 9.0f), 1.0f, 2000.0f);
			mvp = projMatrix * _viewMat * mvp ;
			glUniformMatrix4fv(mvpIn, 1, false, glm::value_ptr(mvp));
			SDL::SDL_Platform::CheckGL();

			//Bind to VAO
			glBindVertexArray(msh->gVAO);
			SDL::SDL_Platform::CheckGL();

			//DRAW
			if (msh->line == true){
				if (msh->strip == true){
					glDrawArrays(GL_LINE_STRIP, 0, msh->numVerts);
				}
				else{
					glDrawArrays(GL_LINES, 0, msh->numVerts);
				}
			}
			else{
				if (msh->fan == true){
					glDrawArrays(GL_TRIANGLE_FAN, 0, msh->numVerts);
				}
				else if (msh->strip == true){
					glDrawArrays(GL_TRIANGLE_STRIP, 0, msh->numVerts);
				}
				else{
					glDrawArrays(GL_TRIANGLES, 0, msh->numVerts);
				}
			}
			SDL::SDL_Platform::CheckGL();

			//unbind VAO
			glBindVertexArray(0);
			SDL::SDL_Platform::CheckGL();

			//Unbind program
			glUseProgram(NULL);
			SDL::SDL_Platform::CheckGL();
		}

		void COGL_Renderer::PrepFrame()
		{

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			glClearDepth(1.0f);
			glViewport(0, 0, SDL::SDL_Platform::GetSreenWidth(), SDL::SDL_Platform::GetSreenHeight());

			// Cull triangles which normal is not towards the camera
			//glEnable(GL_CULL_FACE);
			//glViewport(0,0,1920,1080);

			SDL::SDL_Platform::CheckGL();
			clearSurface();
		}

		void COGL_Renderer::PostRender()
		{
			SDL_GL_SwapWindow(SDL::SDL_Platform::GetWindow());
		}

		void COGL_Renderer::loadShaders()
		{
			//load Default Shaders
			printf("Loading Shaders \n");
			_defaultProgram = new OGL::OGL_ShaderProgram();

			//Create vertex shader
			OGL::OGL_VertexShader * VS = new OGL::OGL_VertexShader();
			VS->LoadSourceShader("shaders/basic.vert");
			SDL::SDL_Platform::CheckGL();

			//Attach vertex shader to program
			_defaultProgram->attachShader(VS);

			//Create Fragment shader
			OGL::OGL_FragmentShader * FS = new OGL::OGL_FragmentShader();
			FS->LoadSourceShader("shaders/basic.frag");
			SDL::SDL_Platform::CheckGL();

			//Attach vertex shader to program
			_defaultProgram->attachShader(FS);
			SDL::SDL_Platform::CheckGL();

			//Link program
			_defaultProgram->link();
		}

		OGL::OGL_ShaderProgram* COGL_Renderer::GetDefaultShaderProgram()
		{
			if (_defaultProgram == nullptr)
			{
				loadShaders();
			}
			return _defaultProgram;
		}
	}
}