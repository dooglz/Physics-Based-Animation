#include "Physics.h"
#include "Physics_Object.h"
#include "Physics_Objects_shapes.h"
#include "Collision_Detection.h"

namespace Physics{
	PhysicsSytem* System = NULL;

	void PhysicsSytem::Init(){
		printf("Hello, I'm a physics engine\n");
		System = this;
		gavity = Vector3(0, -9.81f, 0);
	}

	void PhysicsSytem::Tick(double t, double timeStep)
	{
		//Gravity
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {

		}
		//Integrate
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {
			(*it)->Update(t,timeStep);
		}
		//Detect collisions
		CCollisionDetection::Scan(_scene);

		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {
			//Wololo
		}
		//Integrate again if necessary
	}

	void PhysicsSytem::Shutdown()
	{

	}

	void PhysicsSytem::createPlaneShape(Vector3 normal, float distance)
	{

	}
}