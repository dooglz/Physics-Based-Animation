#pragma once
#include "../Engine/Maths.h"
#include "Physics_Objects_shapes.h"

#include "Physics_Object.h"
#include <vector>

namespace Physics{
	class CCollisionDetection
	{
	public:
		struct Collision
		{
			CPhysicsObject* objectA;
			CPhysicsObject* objectB;
			Vector3 normal;
			Vector3 point;
			float penetration;
		};
	protected:
		static std::vector<Collision*> _collisions;
		static bool SphereSphere(CSphere_Object* A, CSphere_Object* B, bool resolve);
		static bool SphereCuboid(CSphere_Object* A, CCube_Object* B, bool resolve);
		static bool SpherePlane(CSphere_Object* A, CPlane_Object* B, bool resolve);
		static bool CuboidCuboid(CCube_Object* A, CCube_Object* B, bool resolve);
		static bool CuboidPlane(CCube_Object* A, CPlane_Object* B, bool resolve);
		static bool PlanePlane(CPlane_Object* A, CPlane_Object* B, bool resolve);
	public:
		static void Scan(std::vector<CPhysicsObject*> scene);
		static void Resolve();
	};
}