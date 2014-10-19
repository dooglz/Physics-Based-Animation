#include "Physics.h"
#include <stdio.h>
namespace Engine{

	void Physics::Init()
	{

	}

	void Physics::Tick(double t, double timeStep)
	{
		printf("Physics TICK: %d\t%d\n", t,timeStep);
	}

	void Physics::Shutdown()
	{

	}
}