#include "Cm_Physics.h"

namespace Engine{

	CmPhysics::CmPhysics() : Engine::CComponent("Physics")
	{

	}

	CmPhysics::~CmPhysics(){}

	float CmPhysics::GetMass(){ return _mass; }
	void CmPhysics::SetMass(float m){ _mass = m; }
	bool CmPhysics::UsesGravity(){ return  _useGravity; }
	void CmPhysics::SetGravityMode(bool b){ _useGravity = b; }
}