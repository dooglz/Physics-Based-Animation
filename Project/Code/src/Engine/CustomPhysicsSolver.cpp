#include "CustomPhysicsSolver.h"
#include "../Physics/Physics.h"
#include "../Physics/Physics_Object.h"

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
		_po = new Physics::CPhysicsObject();
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