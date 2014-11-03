#include "BulletSolver.h"
#include <stdio.h>
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
namespace Engine{

	void CBulletSolver::Init()
	{
		broadphase = new btDbvtBroadphase();
		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
		dynamicsWorld->setGravity(btVector3(0, -10, 0));
		
	}

	void CBulletSolver::Tick(unsigned long t, unsigned long  timeStep)
	{
	//	printf("Bullet tick\n");
	//	dynamicsWorld->stepSimulation(t, timeStep);
	}

	void CBulletSolver::Shutdown(){
		//delete dynamicsWorld;
		//delete solver;
		//delete dispatcher;
		//delete collisionConfiguration;
		//delete broadphase;
	}
}