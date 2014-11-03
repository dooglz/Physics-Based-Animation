#pragma once
#include "Maths.h"

namespace Engine{
	//Should really be called physicsInterface.
	class CPhysicsSolver
	{
	private:

	protected:

	public:
		CPhysicsSolver(){};
		virtual void Init() = 0;
		virtual void Tick(unsigned long t, unsigned long  timeStep) = 0;
		virtual void Shutdown() = 0;
		virtual void createPlaneShape(Vector3 normal, float distance) = 0;
	};

	//global public reference to the renderer
	extern CPhysicsSolver* PhysicsSolver;
}