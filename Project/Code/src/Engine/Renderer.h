#pragma once
#include "Maths.h"


namespace Engine{
	class Mesh;
	class CRenderer
	{
	private:

	protected:

	public:
		CRenderer(){};
		virtual void renderMesh(Mesh* msh, Matrix4 mvp) = 0;
		virtual void PrepFrame() = 0;
		virtual void PostRender() = 0;
	};

	//global public reference to the renderer
	extern CRenderer* Renderer;
}
