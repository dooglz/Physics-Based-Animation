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

	CPhysicsObject* CCustomSover::CreateCubeObject(float mass, Vector3 position, float lw, float lh, float ld)
	{
		return new CCustomCubePhysicsObject(mass, position, lw, lh, ld);
	}

	CPhysicsObject* CCustomSover::CreateSphereObject(float mass, Vector3 position, float radius)
	{
		
		return new CCustomSpherePhysicsObject(mass, position, radius);
	}

	//---------
	CCustomCubePhysicsObject::CCustomCubePhysicsObject(float mass, Vector3 position, float lw, float lh, float ld)
	{
		_po = new Physics::CCube_Object(mass,position,lw,lh,ld);
	}
	CCustomSpherePhysicsObject::CCustomSpherePhysicsObject(float mass, Vector3 position, float radius)
	{
		_po = new Physics::CSphere_Object(mass, position,radius);
	}
	//---------


	Vector3 CCustomPhysicsObject::getRotation()
	{
		return _po->getRotation();
	}

	Vector3 CCustomPhysicsObject::getPosition()
	{
		return _po->getPosition();
	}

	bool CCustomPhysicsObject::UsesGravity()
	{
		return (_po->usesGravity);
	}
	void CCustomPhysicsObject::SetUsesGravity(bool b)
	{
		_po->usesGravity = b;
	}

	float CCustomPhysicsObject::GetMass()
	{
		return _po->GetMass();
	}

	void CCustomPhysicsObject::SetMass(float m)
	{
		_po->SetMass(m);
	}

}