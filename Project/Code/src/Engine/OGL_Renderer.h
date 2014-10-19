#pragma once
#include "Renderer.h"
#include "Maths.h"

namespace Engine{
	namespace SDL{
		class COGL_Renderer : public CRenderer
		{
		private:

		protected:

		public:
			COGL_Renderer();
			void renderMesh(Mesh* msh, Matrix4 mvp);
			void PrepFrame();
			void PostRender();
			void clearSurface();
		};

	}
}
