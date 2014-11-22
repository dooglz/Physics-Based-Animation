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
		std::vector<Vector3> getDebugLines();
		Vector3 getPosition();
		Quaternion getRotation();
		bool UsesGravity();
		void SetUsesGravity(bool b);
		float GetMass();
		void SetMass(float m);
	};

	class CCustomCubePhysicsObject : public CCustomPhysicsObject
	{
	public:
		CCustomCubePhysicsObject(float mass, Vector3 position, Quaternion rotation, float lw, float lh, float ld);
	};

	class CCustomSpherePhysicsObject : public CCustomPhysicsObject
	{
	public:
		CCustomSpherePhysicsObject(float mass, Vector3 position, Quaternion rotation, float radius);
	};

	class CCustomPlanePhysicsObject : public CCustomPhysicsObject
	{
	public:
		CCustomPlanePhysicsObject(Vector3 position, Vector3 normal);
	};

	class CCustomSover : public CPhysicsSolver{
		
	protected:
		Physics::PhysicsSytem* _system;
	public:
		void Init();
		void Tick(double t, double  timeStep);
		void Shutdown();
		CPhysicsObject* CreateCubeObject(float mass, Vector3 position, Quaternion rotation, float lw, float lh, float ld);
		CPhysicsObject* CreateSphereObject(float mass, Vector3 position, Quaternion rotation, float radius);
		CPhysicsObject* CreatePlaneObject(Vector3 position, Vector3 normal);
	};
}