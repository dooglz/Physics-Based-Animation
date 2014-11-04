#include "Physics.h"

namespace Physics{

	Vector3 CPhysicsObject::getPosition()
	{
		return Vector3(1);
	}

	Vector3 CPhysicsObject::getRotation()
	{
		return Vector3(1);
	}

	void PhysicsSytem::Init(){
		printf("Hello, I'm a physics engine\n");
	}

	void PhysicsSytem::Tick(unsigned long t, unsigned long  timeStep)
	{

	}

	void PhysicsSytem::Shutdown()
	{

	}

	void PhysicsSytem::createPlaneShape(Vector3 normal, float distance)
	{

	}
}