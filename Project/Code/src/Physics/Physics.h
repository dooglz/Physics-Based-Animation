#pragma once
#include "../Engine/Maths.h"
#include <iostream>
#include <Vector>

namespace Physics{

	class CPhysicsObject
	{
	private:

	protected:
		Vector3 _position;
	public:
		CPhysicsObject();
		Vector3 getPosition();
		Vector3 getRotation();
		void setPosition(Vector3 v);
	};

	class PhysicsSytem{

	protected:
		
	public:
		std::vector<CPhysicsObject*> _scene;
		void Init();
		void Tick(unsigned long t, unsigned long  timeStep);
		void Shutdown();
		void createPlaneShape(Vector3 normal, float distance);
	};

	extern PhysicsSytem* System;
}