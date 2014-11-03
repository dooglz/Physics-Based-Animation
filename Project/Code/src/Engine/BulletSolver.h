#pragma once
#include "Physics.h"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

//#include "btBulletDynamicsCommon.h"
//#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
namespace Engine{
	class CBulletSolver : public CPhysicsSolver{

	protected:
		btBroadphaseInterface* broadphase;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
	public:
		void Init();
		void Tick(unsigned long t, unsigned long  timeStep);
		void Shutdown();
	};
}