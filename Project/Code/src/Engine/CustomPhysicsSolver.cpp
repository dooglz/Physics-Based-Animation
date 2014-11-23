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
		if (!PhysicsEnabled){
			return;
		}
		if (!PhysicsTickEnabled){
			t = 0.0;
			timeStep = 0;
		}
		_system->Tick(t, timeStep);
	};

	void  CCustomSover::Shutdown()
	{
		_system->Shutdown();
		delete _system;
	};
	CPhysicsObject* CCustomSover::CreateCubeObject(float mass, Vector3 position, Quaternion rotation, float lw, float lh, float ld)
	{
		return new CCustomCubePhysicsObject(mass, position, rotation, lw, lh, ld);
	}

	CPhysicsObject* CCustomSover::CreateSphereObject(float mass, Vector3 position, Quaternion rotation, float radius)
	{
		return new CCustomSpherePhysicsObject(mass, position, rotation, radius);
	}

	CPhysicsObject* CCustomSover::CreatePlaneObject(Vector3 position, Vector3 normal)
	{
		return new CCustomPlanePhysicsObject(position, normal);
	}

	//---------
	CCustomCubePhysicsObject::CCustomCubePhysicsObject(float mass, Vector3 position, Quaternion rotation,  float lw, float lh, float ld)
	{
		_po = new Physics::CCube_Object(mass,position,rotation,lw,lh,ld);
	}
	CCustomSpherePhysicsObject::CCustomSpherePhysicsObject(float mass, Vector3 position, Quaternion rotation, float radius)
	{
		_po = new Physics::CSphere_Object(mass, position,rotation,radius);
	}

	CCustomPlanePhysicsObject::CCustomPlanePhysicsObject(Vector3 position, Vector3 normal)
	{
		_po = new Physics::CPlane_Object(position, normal);
	}


	//---------


	Quaternion CCustomPhysicsObject::getRotation()
	{
		return _po->GetOrientation();
	}

	Vector3 CCustomPhysicsObject::getPosition()
	{
		return _po->GetPosition();
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
	std::vector<Vector3> CCustomPhysicsObject::getDebugLines()
	{
		return _po->getDebugLines();
	}
}