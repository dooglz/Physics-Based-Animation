#include "Cm_Physics.h"
#include "Entity.h"
#include "Renderer.h"

namespace Engine{

	CmPhysics::CmPhysics() : Engine::CComponent("Physics")
	{
		_showdebug = true;
	}

	CmPhysics::~CmPhysics(){}

	float CmPhysics::GetMass(){ return _mass; }
	void CmPhysics::SetMass(float m){ _mass = m; }
	bool CmPhysics::UsesGravity(){ return  _useGravity; }
	void CmPhysics::SetGravityMode(bool b){ _useGravity = b; }

	void CmPhysics::Render()
	{
		if (_showdebug)
		{
			Renderer->DrawLine(Vector3(0.0f), Ent->getPosition());
		}
	}
}