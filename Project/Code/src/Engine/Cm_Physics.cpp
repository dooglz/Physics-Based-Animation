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
		Ent->setPosition(_po->getPosition());
		Ent->setRotation(_po->getRotation());
	}

	void CmPhysics::Render()
	{
		if (_showdebug)
		{
			Renderer->DrawLine(Vector3(0.0f), Ent->getPosition());
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
}