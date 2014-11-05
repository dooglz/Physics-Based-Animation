#pragma once
#include "../Engine/Maths.h"
#include <iostream>
#include <Vector>

namespace Physics{
	class CPhysicsObject;
	class PhysicsSytem{

	protected:
		
	public:
		std::vector<CPhysicsObject*> _scene;
		void Init();
		void Tick(double t, double timeStep);
		void Shutdown();
		void createPlaneShape(Vector3 normal, float distance);
	};

	extern PhysicsSytem* System;
}