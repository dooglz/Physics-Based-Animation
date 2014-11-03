#pragma once
#include "Component.h"

namespace Engine{
	class CollisionMesh;
	class CmPlanecollider : public CComponent{

	protected:
		CollisionMesh* _cm;
		bool _showdebug;
	public:
		CmPlanecollider();
		~CmPlanecollider();

		void Render();
		//void Update(double delta);

	};
}