//The main breakway point for the physics simulation

#pragma once
#include "../Engine/Maths.h"
#include <iostream>
#include <Vector>

namespace Physics{
	class CPhysicsObject;
	class PhysicsSytem{

	protected:
		
	public:
		Vector3 gavity;
		std::vector<CPhysicsObject*> _scene;
		void Init();
		void Tick(const double t, const double timeStep);
		void Shutdown();
	};

	extern PhysicsSytem* System;
}