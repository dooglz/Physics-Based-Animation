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
		Resolve();
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


	///
	void CCollisionDetection::Resolve()
	{
		for (int i = 0; i < _collisions.size(); i++)
		{
			Collision* c = _collisions[i];
			CPhysicsObject* objectA = c->objectA;
			CPhysicsObject* objectB = c->objectB;
			// Some simple check code.
		
			const float invMass0 = objectA->GetInvMass();
			const float invMass1 = objectB->GetInvMass();
			const Matrix3 InvInertia0 = objectA->GetInvTensor();
			const Matrix3 InvInertia1 = objectB->GetInvTensor();
			
			// Both objects are non movable
			if ((invMass0 + invMass1) == 0.0) return;
			Vector3 r0 = c->point - objectA->getPosition();
			Vector3 r1 = c->point - objectB->getPosition();
			Vector3 v0 = objectA->GetLinearVeloicty() + Cross(objectA->GetAngularVeloicty(), r0);
			Vector3 v1 = objectB->GetLinearVeloicty() + Cross(objectB->GetAngularVeloicty(), r1);
		
			// Relative Velocity
			Vector3 dv = v0 - v1;
			
			// If the objects are moving away from each other
			// we dont need to apply an impulse
			float relativeMovement = -Dot(dv, c->normal);
			if (relativeMovement < -0.01f)
			{
				return;
			}
			
			// NORMAL Impulse
			{
				// Coefficient of Restitution
				float e = 0.0f;
				/*
				float normDiv = 
				Dot(c->normal, c->normal) * 
				((invMass0 + invMass1) + Dot( c->normal,
					Cross(
						Transform(Cross(r0, c->normal),InvInertia0), 
						r0)
					+ Cross(
						Transform(Cross(r1, c->normal), InvInertia1)
						, r1)
					));
				*/
				float jn = -1 * (1 + e)*Dot(dv, c->normal);// / normDiv;
			
				// Hack fix to stop sinking
				// bias impulse proportional to penetration distance
				jn = jn + (c->penetration*1.5f);
				
				objectA->AddImpulse(invMass0 * c->normal * jn*300.0f);
			//	c0.m_linVelocity += invMass0 * c->normal * jn;
			//  c0.m_angVelocity += Transform(Cross(r0, c->normal * jn),InvInertia0);
				objectB->AddImpulse(-1.0f* invMass1 * c->normal * jn);
			//	c1.m_linVelocity -= invMass1 * c->normal * jn;
			//	c1.m_angVelocity -= Transform(Cross(r1, c->normal * jn),InvInertia1);
			}
			/*
			// TANGENT Impulse Code
			{
				// Work out our tangent vector , with is perpendicular
				// to our collision normal
				Vector3 tangent = Vector3(0, 0, 0);
				tangent = dv - (Dot(dv, normal) * normal);
				tangent = Normalize(tangent);
			
				float tangDiv = invMass0 + invMass1
				+ Dot(tangent, Cross((Cross(r0, tangent)
				* c0.m_invInertia), r0)
				+ Cross((Cross(r1, tangent) * c1.m_invInertia), r1));
			
				float jt = -1 * Dot(dv, tangent) / tangDiv;
				// Clamp min/max tangental component
			
				// Apply contact impulse
				c0.m_linVelocity += invMass0 * tangent * jt;
				c0.m_angVelocity += Transform(Cross(r0, tangent * jt),InvInertia0);
			
				c1.m_linVelocity -= invMass1 * tangent * jt;
				c1.m_angVelocity -= Transform(Cross(r1, tangent * jt),InvInertia1);
			} // TANGENT
			*/
			delete c;
		}
		_collisions.clear();
	}

}