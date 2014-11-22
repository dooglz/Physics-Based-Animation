#pragma once
#include "Physics_Object.h"

namespace Physics{
	class CCube_Object : public CPhysicsObject
	{
		protected:
			Vector3 _size;
			Matrix4 CalculateInverseInertiaTensor();
			std::vector<Vector3> getDebugLines();
		public:
			CCube_Object(const float mass, const Vector3& position, const  Quaternion& rotation, const float lw, const float lh, const float ld);
			Vector3 GetSize() { return _size; }
	};

	class CPlane_Object : public CPhysicsObject
	{
	protected:
		Vector3 _normal;
		Matrix4 CalculateInverseInertiaTensor();
		std::vector<Vector3> getDebugLines();
	public:
		CPlane_Object(const Vector3& position, const Vector3& normal);
		Vector3 GetNormal(){ return _normal; }
	};

	class CSphere_Object : public CPhysicsObject
	{
		protected:
			Matrix4 CalculateInverseInertiaTensor();
			std::vector<Vector3> getDebugLines();
			float _radius;
		public:
			CSphere_Object(const float mass, const Vector3& position, const  Quaternion& rotation, const float radius);
			float GetRadius(){ return _radius; }
	};
}