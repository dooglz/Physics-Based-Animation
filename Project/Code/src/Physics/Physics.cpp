#include "Physics.h"

namespace Physics{
	PhysicsSytem* System = NULL;

	Vector3 CPhysicsObject::getPosition()
	{
		return _position;
	}

	Vector3 CPhysicsObject::getRotation()
	{
		return Vector3(0);
	}

	void CPhysicsObject::setPosition(Vector3 v)
	{
		_position = v;
	}

	void PhysicsSytem::Init(){
		printf("Hello, I'm a physics engine\n");
		System = this;
	}

	CPhysicsObject::CPhysicsObject()
	{
		printf("Hello, I'm a new physics object\n");
		System->_scene.push_back(this);
	}

	void PhysicsSytem::Tick(unsigned long t, unsigned long  timeStep)
	{
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {
			(*it)->setPosition((*it)->getPosition() + Vector3(0, 0.001, 0));
		}
	}

	void PhysicsSytem::Shutdown()
	{

	}

	void PhysicsSytem::createPlaneShape(Vector3 normal, float distance)
	{

	}
}