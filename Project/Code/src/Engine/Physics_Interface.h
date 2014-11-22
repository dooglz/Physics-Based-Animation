#pragma once
#include "Maths.h"
#include <vector>

namespace Engine{
	//Should really be called physicsInterface.

	class CPhysicsObject
	{
	private:

	protected:

	public:
		CPhysicsObject(){};
		virtual Vector3 getPosition() = 0;
		virtual Quaternion getRotation() = 0;
		virtual float GetMass() = 0;
		virtual void SetMass(float m) = 0;
		virtual bool UsesGravity() = 0;
		virtual void SetUsesGravity(bool b) = 0;
		virtual std::vector<Vector3> getDebugLines() = 0;
	};

	class CPhysicsSolver
	{
	private:

	protected:

	public:
		CPhysicsSolver(){};
		virtual void Init() = 0;
		virtual void Tick(double t, double  timeStep) = 0;
		virtual void Shutdown() = 0;
		virtual void createPlaneShape(Vector3 normal, float distance) = 0;
		virtual CPhysicsObject* CreateCubeObject(float mass, Vector3 position, Quaternion rotation, float lw, float lh, float ld) = 0;
		virtual CPhysicsObject* CreateSphereObject(float mass, Vector3 position, Quaternion rotation, float radius) = 0;
		virtual CPhysicsObject* CreatePlaneObject(Vector3 position, Vector3 normal) = 0;
	};

	//global public reference to the renderer
	extern CPhysicsSolver* PhysicsSolver;
	extern bool PhysicsTickEnabled;


}