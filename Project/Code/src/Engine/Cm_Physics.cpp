#include "Cm_Physics.h"
#include "Entity.h"
#include "Renderer.h"
#include "Physics_Interface.h"

namespace Engine{
	CmPhysics::CmPhysics(std::string s) : Engine::CComponent(s)
	{
		_showdebug = true;
	}

	CmPhysics::~CmPhysics(){}

	float CmPhysics::GetMass(){ return _po->GetMass(); }
	void CmPhysics::SetMass(float m){ _po->SetMass(m); }
	bool CmPhysics::UsesGravity(){ return  _po->UsesGravity(); }
	void CmPhysics::SetUsesGravity(bool b){ _po->SetUsesGravity(b); }

	void CmPhysics::Update(double delta)
	{
		Vector3 v = _po->getPosition();
		Ent->setPosition(v);
		Ent->setRotation(_po->getRotation());
	}
	void CmPhysics::Render()
	{
		if (_showdebug)
		{
			Renderer->DrawLine(Vector3(0.0f), Ent->getPosition());
			std::vector<Vector3> arr = _po->getDebugLines();
			for (unsigned int i = 0; i < arr.size();)
			{
				Vector3 a = arr[i];
				Vector3 b = arr[i + 1];
				Renderer->DrawLine(arr[i], arr[i+1]);
				i += 2;
			}
		}
	}
	//--

	CmPhysics_Cuboid::CmPhysics_Cuboid(float mass, Vector3 position, float lw, float lh, float ld) :CmPhysics("Physics Cuboid")
	{
		_po = PhysicsSolver->CreateCubeObject(mass, position, lw, lh, ld);
	}

	CmPhysics_Cuboid::~CmPhysics_Cuboid()
	{}

	CmPhysics_Sphere::CmPhysics_Sphere(float mass, Vector3 position, float radius) :CmPhysics("Physics Sphere")
	{
		_po = PhysicsSolver->CreateSphereObject(mass, position, radius);
	}

	CmPhysics_Sphere::~CmPhysics_Sphere()
	{}
	
	CmPhysics_Plane::CmPhysics_Plane(Vector3 position,Vector3 normal) :CmPhysics("Physics Plane")
	{
		_po = PhysicsSolver->CreatePlaneObject(position, normal);
	}

	CmPhysics_Plane::~CmPhysics_Plane()
	{}
}