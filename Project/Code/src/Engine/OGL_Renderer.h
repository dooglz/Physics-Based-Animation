#pragma once
#include "Renderer.h"
#include "Maths.h"

namespace Engine{
	namespace OGL{
		class OGL_ShaderProgram;
		class COGL_Renderer : public CRenderer
		{
		private:

		protected:
			static OGL::OGL_ShaderProgram* _defaultProgram;
			static void loadShaders();
		public:
			COGL_Renderer();
			void renderMesh(Mesh* msh, Matrix4 mvp);
			void PrepFrame();
			void PostRender();
			void clearSurface();
			//
			static OGL::OGL_ShaderProgram* GetDefaultShaderProgram();
		};

	}
}
