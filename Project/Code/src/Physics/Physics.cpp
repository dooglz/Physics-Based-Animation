#include "Physics.h"
#include "Physics_Object.h"

namespace Physics{
	PhysicsSytem* System = NULL;

	void PhysicsSytem::Init(){
		printf("Hello, I'm a physics engine\n");
		System = this;
	}

	void PhysicsSytem::Tick(double t, double timeStep)
	{
		//Check collision
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {
			(*it)->AddForce(Vector3(0, 1.0f, 0));
		}
		//Integrate
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {
			(*it)->Update(t,timeStep);
		}
	}

	void PhysicsSytem::Shutdown()
	{

	}

	void PhysicsSytem::createPlaneShape(Vector3 normal, float distance)
	{

	}
}