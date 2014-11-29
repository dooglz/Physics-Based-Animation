//Collision detection Headder
//This class is respoinsible for detecting any collsisions between obejcts in the scene and creating a collsission object for them
//This also hosts the resolve function which takes the collsiones and resolves them to impulses.

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
			CPhysicsObject* const objectA;
			CPhysicsObject* const objectB;
			const Vector3 normal;
			const Vector3 point;
			const float penetration;
			Collision(CPhysicsObject* const A, CPhysicsObject* const B, Vector3 n, Vector3 p, float pn) : objectA(A), objectB(B), normal(n), point(p), penetration(pn){}
		};
	protected:
		static std::vector<Collision*> _collisions;
		static bool SphereSphere(CSphere_Object* const  A, CSphere_Object* const B, const bool resolve);
		static bool SphereCuboid(CSphere_Object* const A, CCube_Object* B, const bool resolve);
		static bool SpherePlane(CSphere_Object* const A, CPlane_Object* const B, const bool resolve);
		static bool CuboidCuboid(CCube_Object* const A,  CCube_Object* const B, const bool resolve);
		static bool CuboidPlane(CCube_Object* const A, CPlane_Object* const B, const bool resolve);
		static bool PlanePlane(CPlane_Object* const A, CPlane_Object* const B, const bool resolve);
		static void CCollisionDetection::CollisionRouter(CPhysicsObject* objA, CPhysicsObject* objB);
	public:
		static void Scan(const std::vector<CPhysicsObject*>& scene);
		static void Resolve();
	};
}