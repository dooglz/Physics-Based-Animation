#include "Physics.h"
#include "Physics_Object.h"

#include "Collision_Detection.h"

namespace Physics{
	PhysicsSytem* System = NULL;

	void PhysicsSytem::Init(){
		printf("Hello, I'm a physics engine\n");
		System = this;
		gavity = Vector3(0, -9.81f, 0);
	}

	void PhysicsSytem::Tick(const double t, const  double timeStep)
	{
		//Integrate
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {
			(*it)->Integrate(t,timeStep);
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
}