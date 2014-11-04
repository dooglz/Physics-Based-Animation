#include "Cm_Physics.h"
#include "Entity.h"
#include "Renderer.h"
#include "Physics.h"

namespace Engine{

	CmPhysics::CmPhysics() : Engine::CComponent("Physics")
	{
		_showdebug = true;
		//create a physics Object
		_po = PhysicsSolver->CreateObject();
	}

	CmPhysics::~CmPhysics(){}

	float CmPhysics::GetMass(){ return _mass; }
	void CmPhysics::SetMass(float m){ _mass = m; }
	bool CmPhysics::UsesGravity(){ return  _useGravity; }
	void CmPhysics::SetGravityMode(bool b){ _useGravity = b; }

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
}