#pragma once
#include "../Engine/Maths.h"
#include <iostream>
#include <Vector>

namespace Physics{

	class CPhysicsObject
	{
	private:

	protected:
		
		Vector3 _rotation;
		//---
		
		
		
	public:
		Vector3 _position;
		Vector3 _velocity;
		float mass = 1.0f;
		Vector3 _forces;
		CPhysicsObject();
		Vector3 getPosition();
		Vector3 getRotation();
		void setPosition(Vector3 v);
		void setRotation(Vector3 v);
	};

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