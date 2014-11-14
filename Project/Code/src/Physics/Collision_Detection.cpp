#include "Collision_Detection.h"

namespace Physics{
	std::vector<CCollisionDetection::Collision*> CCollisionDetection::_collisions;
	
	void CCollisionDetection::Scan(std::vector<CPhysicsObject*> scene)
	{
		//foreach object
		for (int i = 0; i < scene.size(); i++)
		{
			CPhysicsObject* objA = scene[i];

			for (int j = i+1; j < scene.size(); j++)
			{
				CPhysicsObject* objB = scene[j];
				//BROADPHASE

				float distance = Distance(objA->getPosition(),objB->getPosition());
				if (distance < (1.0f))
				{
					//Collision!
					Collision* c = new Collision();
					c->objectA = objA;
					c->objectB = objB;
					c->normal = Vector3(0, 1, 0);
				}
			}
		}
	}
}