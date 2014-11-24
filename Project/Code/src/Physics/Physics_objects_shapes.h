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
			~CCube_Object(){}
			Vector3 GetSize() const { return _size; }
	};

	class CPlane_Object : public CPhysicsObject
	{
	protected:
		Vector3 _normal;
		Matrix4 CalculateInverseInertiaTensor();
		std::vector<Vector3> getDebugLines();
	public:
		CPlane_Object(const Vector3& position, const Vector3& normal);
		~CPlane_Object(){}
		Vector3 GetNormal()const { return _normal; }
	};

	class CSphere_Object : public CPhysicsObject
	{
		protected:
			Matrix4 CalculateInverseInertiaTensor();
			std::vector<Vector3> getDebugLines();
			float _radius;
			
		public:
			CSphere_Object(const float mass, const Vector3& position, const  Quaternion& rotation, const float radius);
			~CSphere_Object(){}
			float GetRadius()const { return _radius; }
	};
}