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

				//get the types
				if (objA->type == CPhysicsObject::SPHERE)
				{
					if (objB->type == CPhysicsObject::SPHERE)
					{
						SphereSphere(static_cast<CSphere_Object*>(objA), static_cast<CSphere_Object*>(objB));
					}
					else if (objB->type == CPhysicsObject::CUBEOID)
					{
						SphereCuboid(static_cast<CSphere_Object*>(objA), static_cast<CCube_Object*>(objB));
					}
					else if (objB->type == CPhysicsObject::PLANE)
					{
						SpherePlane(static_cast<CSphere_Object*>(objA), static_cast<CPlane_Object*>(objB));
					}
				}
				else if(objA->type == CPhysicsObject::CUBEOID)
				{
					if (objB->type == CPhysicsObject::SPHERE)
					{
						SphereCuboid(static_cast<CSphere_Object*>(objB), static_cast<CCube_Object*>(objA));
					}
					else if (objB->type == CPhysicsObject::CUBEOID)
					{
						CuboidCuboid(static_cast<CCube_Object*>(objA), static_cast<CCube_Object*>(objB));
					}
					else if (objB->type == CPhysicsObject::PLANE)
					{
						CuboidPlane(static_cast<CCube_Object*>(objA), static_cast<CPlane_Object*>(objB));
					}
				}
				else if (objA->type == CPhysicsObject::PLANE)
				{
					if (objB->type == CPhysicsObject::SPHERE)
					{
						SpherePlane(static_cast<CSphere_Object*>(objA), static_cast<CPlane_Object*>(objB));
					}
					else if (objB->type == CPhysicsObject::CUBEOID)
					{
						CuboidPlane(static_cast<CCube_Object*>(objB), static_cast<CPlane_Object*>(objA));
					}
					else if (objB->type == CPhysicsObject::PLANE)
					{
						PlanePlane(static_cast<CPlane_Object*>(objA), static_cast<CPlane_Object*>(objB));
					}
				}

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

	void CCollisionDetection::SphereSphere(CSphere_Object* a, CSphere_Object* b)
	{
		printf("SphereSphere!\n");
	}

	void CCollisionDetection::SphereCuboid(CSphere_Object* a, CCube_Object* b)
	{
		printf("SphereCuboid!\n");
	}

	void CCollisionDetection::SpherePlane(CSphere_Object* a, CPlane_Object* b)
	{
		printf("SpherePlane!\n");
	}

	void CCollisionDetection::CuboidCuboid(CCube_Object* a, CCube_Object* b)
	{
		printf("CuboidCuboid!\n");
	}

	void CCollisionDetection::CuboidPlane(CCube_Object* a, CPlane_Object* b)
	{
		
		//assumme all plane are flat for now
		float distance = -1.0f*b->getPosition().y;
		//assume perfect sqaure
		float radius = a->GetSize().x;

		float separation = Dot(a->getPosition(), b->GetNormal()) + distance;
		if (separation > radius)
		{
			//return false;
			return;
		}
		printf("CuboidPlane Collision!\n");
		//Collision!
		Collision* c = new Collision();
		c->objectA = a;
		c->objectB = b;
		c->normal = b->GetNormal();
		c->penetration = radius - separation;
		c->point = a->getPosition() - b->GetNormal() * separation;
		_collisions.push_back(c);
		//return true;
		return;

	}

	void CCollisionDetection::PlanePlane(CPlane_Object* A, CPlane_Object* B)
	{
		printf("PlanePlane!\n");
	}

}