#include "Cm_Planecollider.h"
#include "Entity.h"
#include "Renderer.h"
//#include "Physics.h"

namespace Engine{

	CmPlanecollider::CmPlanecollider() : Engine::CComponent("PlaneCollider")
	{
		_showdebug = true;
	//	PhysicsSolver->createPlaneShape(Vector3(0, 1, 0), 1);
	}

	CmPlanecollider::~CmPlanecollider(){}


	void CmPlanecollider::Render()
	{
		if (_showdebug)
		{
			Renderer->DrawLine(Vector3(0.0f), Ent->getPosition());
		}
	}
}