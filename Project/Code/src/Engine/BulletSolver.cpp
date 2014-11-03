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
		//bullet takes things in seconds
		dynamicsWorld->stepSimulation(((btScalar)t)*0.000001, (((btScalar)timeStep)*0.000001));
	}

	void CBulletSolver::Shutdown(){
		delete dynamicsWorld;
		delete solver;
		delete dispatcher;
		delete collisionConfiguration;
		delete broadphase;
	}
}