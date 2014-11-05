#include "CustomPhysicsSolver.h"
#include "../Physics/Physics.h"
#include "../Physics/Physics_Objects_shapes.h"

namespace Engine{
	void CCustomSover::Init()
	{
		_system = new Physics::PhysicsSytem();
		_system->Init();
	};

	void  CCustomSover::Tick(double t, double  timeStep){
		_system->Tick(t, timeStep);
	};

	void  CCustomSover::Shutdown()
	{
		_system->Shutdown();
		delete _system;
	};

	void  CCustomSover::createPlaneShape(Vector3 normal, float distance)
	{
		_system->createPlaneShape(normal, distance);
	};

	CPhysicsObject* CCustomSover::CreateObject()
	{
		return new CCustomPhysicsObject();
	}

	//---------

	CCustomPhysicsObject::CCustomPhysicsObject()
	{
		_po = new Physics::CCube_Object(10, Vector3(0), 1, 1, 1);
	}

	Vector3 CCustomPhysicsObject::getRotation()
	{
		return _po->getRotation();
	}

	Vector3 CCustomPhysicsObject::getPosition()
	{
		return _po->getPosition();
	}
}