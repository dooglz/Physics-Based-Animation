#pragma once
#include "../Engine/Maths.h"
#include <iostream>

namespace Physics{

	class CPhysicsObject
	{
	private:

	protected:

	public:
		Vector3 getPosition();
		Vector3 getRotation();
	};

	class PhysicsSytem{

	protected:

	public:
		void Init();
		void Tick(unsigned long t, unsigned long  timeStep);
		void Shutdown();
		void createPlaneShape(Vector3 normal, float distance);
	};
}