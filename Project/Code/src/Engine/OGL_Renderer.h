#pragma once
#include "Renderer.h"
#include "Maths.h"
#include <vector>

namespace Engine{
	namespace OGL{
		class OGL_ShaderProgram;
		class COGL_Renderer : public CRenderer
		{
		private:

		protected:
			static OGL::OGL_ShaderProgram* _defaultProgram;
			static void loadShaders();
			static std::vector<Vector3> linebuffer;
			void ProcessLines();
		public:
			COGL_Renderer();
			void renderMesh(Mesh* msh, Matrix4 mvp);
			void DrawLine(Vector3 p1, Vector3 p2);
			void PrepFrame();
			void PostRender();
			void clearSurface();
			//
			static OGL::OGL_ShaderProgram* GetDefaultShaderProgram();
		};

	}
}
