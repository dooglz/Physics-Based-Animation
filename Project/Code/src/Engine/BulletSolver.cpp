#include "BulletSolver.h"
//#include "btBulletDynamicsCommon.h"
//#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include <stdio.h>

namespace Engine {

void CBulletSolver::Init() {
  /*	broadphase = new btDbvtBroadphase();
          collisionConfiguration = new btDefaultCollisionConfiguration();
          dispatcher = new btCollisionDispatcher(collisionConfiguration);
          btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
          solver = new btSequentialImpulseConstraintSolver;
          dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase,
     solver, collisionConfiguration);
          dynamicsWorld->setGravity(btVector3(0, -10, 0));*/
}
void CBulletSolver::createPlaneShape(Vector3 normal, float distance) {
  //	btCollisionShape* shape = new btStaticPlaneShape(btVector3(normal.x,
  //normal.y, normal.z), 1);
}

void CBulletSolver::Tick(unsigned long t, unsigned long timeStep) {
  //	printf("Bullet tick\n");
  // bullet takes things in seconds
  //	dynamicsWorld->stepSimulation(((btScalar)t)*0.000001,
  //(((btScalar)timeStep)*0.000001));
}

void CBulletSolver::Shutdown() {
  /*	delete dynamicsWorld;
          delete solver;
          delete dispatcher;
          delete collisionConfiguration;
          delete broadphase;*/
}
}