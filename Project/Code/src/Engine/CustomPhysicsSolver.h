#pragma once
#include "Physics_Interface.h"

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
		Vector3 getPosition();
		Vector3 getRotation();
		bool UsesGravity();
		void SetUsesGravity(bool b);
		float GetMass();
		void SetMass(float m);
	};

	class CCustomCubePhysicsObject : public CCustomPhysicsObject
	{
	public:
		CCustomCubePhysicsObject(float mass, Vector3 position, float lw, float lh, float ld);
	};
	class CCustomSpherePhysicsObject : public CCustomPhysicsObject
	{
	public:
		CCustomSpherePhysicsObject(float mass, Vector3 position, float radius);
	};

	class CCustomSover : public CPhysicsSolver{
		
	protected:
		Physics::PhysicsSytem* _system;
	public:
		void Init();
		void Tick(double t, double  timeStep);
		void Shutdown();
		void createPlaneShape(Vector3 normal, float distance);
		CPhysicsObject* CreateCubeObject(float mass, Vector3 position, float lw, float lh, float ld);
		CPhysicsObject* CreateSphereObject(float mass, Vector3 position, float radius);
	};
}