#pragma once
#include "../Engine/Maths.h"
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
		};
	protected:
		static std::vector<Collision*> _collisions;
	public:
		static void Scan(std::vector<CPhysicsObject*> scene);
	};
}