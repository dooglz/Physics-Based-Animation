#pragma once
#include "Maths.h"

namespace Engine{
	class FrustumG {

	private:

		enum {
			TOP = 0, BOTTOM, LEFT,
			RIGHT, NEARP, FARP
		};

	public:

		static enum { OUTSIDE, INTERSECT, INSIDE };
		Plane pl[6];
		Vector3 ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
		float nearD, farD, ratio, angle, tang;
		float nw, nh, fw, fh;

		Vector3 aap;
		Vector3 aan;

		FrustumG(){};
		~FrustumG(){};

		void setCamInternals(float angle, float ratio, float nearD, float farD);
		void setCamDef(Vector3 &p, Vector3 &l, Vector3 &u);
		int pointInFrustum(Vector3 &p);
		int sphereInFrustum(Vector3 &p, float radius);
		int FrustumG::pointAInFrustum(Vector3 &p);

	};

	class Mesh;
	class CRenderer
	{
	private:

	protected:
		Matrix4 _viewMat;
		Matrix4 _projectionMat;
		Matrix4 _viewprojectionMat;
		FrustumG _viewFrustum;
	public:
		CRenderer();
		FrustumG GetFrustum(){ return _viewFrustum; }
		virtual void SetViewMatrix(const Matrix4& vm);
		virtual void renderMesh(Mesh*const msh, const Matrix4& mvp) = 0;
		virtual void DrawLine(const Vector3& p1, const Vector3& p2) = 0;
		virtual void DrawCross(const Vector3& p1, const float size) = 0;
		virtual void PrepFrame() = 0;
		virtual void PostRender() = 0;
	};

	//global public reference to the renderer
	extern CRenderer* Renderer;
}
