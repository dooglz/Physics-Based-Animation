#pragma once
#include "Maths.h"

namespace Engine{
	class Mesh;
	class CRenderer
	{
	private:

	protected:
		//! Number of surfaces/buffers to init.
		const static int _numberOfSurfaces = 2;	//in this case just 2, Front and back buffers.
		Matrix4 _viewMat;
		Matrix4 _projectionMat;
		Matrix4 _viewprojectionMat;
	public:
		CRenderer();
		virtual void SetViewMatrix(const Matrix4& vm);
		virtual void renderMesh(Mesh*const msh, const Matrix4& mvp) = 0;
		virtual void DrawLine(const Vector3& p1, const Vector3& p2) = 0;
		virtual void DrawCross(const Vector3& p1, const float size) = 0;
		virtual void PrepFrame() = 0;
		virtual void PostRender() = 0;
		Vector3 aap;
		Vector3 aan;
	};

	//global public reference to the renderer
	extern CRenderer* Renderer;
}