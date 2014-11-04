#pragma once
#include "Component.h"

namespace Engine{
	class CPhysicsObject;
	class CmPhysics : public CComponent{

	protected:
		float _mass;
		bool _useGravity;
		bool _showdebug;
		CPhysicsObject* _po;
	public:
		CmPhysics();
		~CmPhysics();

		void Render();
		void Update(double delta);

		float GetMass();
		void SetMass(float m);
		bool UsesGravity();
		void SetGravityMode(bool b);
	};
}