#pragma once
#include "Maths.h"


namespace Engine{
	class Mesh;
	class CRenderer
	{
	private:

	protected:
		Matrix4 _viewMat;
	public:
		CRenderer(){};
		virtual void SetViewMatrix(Matrix4 vm);
		virtual void renderMesh(Mesh* msh, Matrix4 mvp) = 0;
		virtual void DrawLine(Vector3 p1, Vector3 p2) = 0;
		virtual void DrawCross(Vector3 p1, float size) = 0;
		virtual void PrepFrame() = 0;
		virtual void PostRender() = 0;
	};

	//global public reference to the renderer
	extern CRenderer* Renderer;
}
