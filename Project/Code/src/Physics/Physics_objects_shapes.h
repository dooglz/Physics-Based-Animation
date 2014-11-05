#pragma once
#include "Physics_Object.h"

namespace Physics{
	class CCube_Object : public CPhysicsObject
	{
		protected:
			Vector3 _size;
			Matrix3 CalculateInertiaTensor();
		public:
			CCube_Object(float mass, Vector3 position, float lw, float lh, float ld);
	};

	class CSphere_Object : public CPhysicsObject
	{
		protected:
			Matrix3 CalculateInertiaTensor();
			float _radius;
		public:
			CSphere_Object(float mass, Vector3 position, float radius);
	};
}