#pragma once
#include "Physics.h"

namespace Physics{
	class PhysicsSytem;
	class CPhysicsObject;
}

namespace Engine{

	class CCustomPhysicsObject : public CPhysicsObject{
	private:

	protected:
		Physics::CPhysicsObject* _po;
	public:
		CCustomPhysicsObject();
		Vector3 getPosition();
		Vector3 getRotation();
	};

	class CCustomSover : public CPhysicsSolver{
		
	protected:
		Physics::PhysicsSytem* _system;
	public:
		void Init();
		void Tick(unsigned long t, unsigned long  timeStep);
		void Shutdown();
		void createPlaneShape(Vector3 normal, float distance);
		CPhysicsObject* CreateObject();
	};
}