#pragma once
#include "Physics_Object.h"

namespace Physics{
	class CCube_Object : public CPhysicsObject
	{
		protected:
			Vector3 _size;
			Matrix3 CalculateInertiaTensor();
			std::vector<Vector3> getDebugLines();
		public:
			CCube_Object(float mass, Vector3 position, float lw, float lh, float ld);
			Vector3 GetSize() { return _size; }
	};

	class CPlane_Object : public CPhysicsObject
	{
	protected:
		Vector3 _normal;
		Matrix3 CalculateInertiaTensor();
		std::vector<Vector3> getDebugLines();
	public:
		CPlane_Object(Vector3 position, Vector3 normal);
		Vector3 GetNormal(){ return _normal; }
	};

	class CSphere_Object : public CPhysicsObject
	{
		protected:
			Matrix3 CalculateInertiaTensor();
			std::vector<Vector3> getDebugLines();
			float _radius;
		public:
			CSphere_Object(float mass, Vector3 position, float radius);
	};
}