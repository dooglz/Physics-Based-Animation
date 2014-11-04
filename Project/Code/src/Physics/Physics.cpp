#include "Physics.h"

namespace Physics{
	PhysicsSytem* System = NULL;

	Vector3 CPhysicsObject::getPosition()
	{
		return _position;
	}

	Vector3 CPhysicsObject::getRotation()
	{
		return _rotation;
	}

	void CPhysicsObject::setPosition(Vector3 v)
	{
		_position = v;
	}

	void CPhysicsObject::setRotation(Vector3 v)
	{
		_rotation = v;
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

	void PhysicsSytem::Tick(double t, double timeStep)
	{
		//Check collision
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {
			//(*it)->setPosition((*it)->getPosition() + Vector3(0, 0.1*sin(0.00001*t), 0.1*cos(0.00001*t)));
			//(*it)->setRotation(Vector3(0, 0.1*sin(0.00001*t), 0.1*cos(0.00001*t)));
			(*it)->_forces += Vector3(0, 1.0f, 0);
		}
		//Integrate
		for (std::vector<CPhysicsObject*>::iterator it = _scene.begin(); it != _scene.end(); ++it) {

			Vector3 acceleration = (*it)->_forces / (*it)->mass;
			(*it)->_velocity += acceleration * (float)timeStep;
			(*it)->_position += (*it)->_velocity * (float)timeStep;
			(*it)->_forces = Vector3(0);
		}
	}

	void PhysicsSytem::Shutdown()
	{

	}

	void PhysicsSytem::createPlaneShape(Vector3 normal, float distance)
	{

	}
}