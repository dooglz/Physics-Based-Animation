#include "Collision_Detection.h"
#include "../Engine/Renderer.h"
#include "../Engine/Utilities.h"

namespace Physics{
	std::vector<CCollisionDetection::Collision*> CCollisionDetection::_collisions;
	
	void CCollisionDetection::Scan(std::vector<CPhysicsObject*> scene)
	{
		//foreach object
		for (unsigned int i = 0; i < scene.size(); i++)
		{
			CPhysicsObject* objA = scene[i];

			for (unsigned int j = i + 1; j < scene.size(); j++)
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
			}
		}
		Resolve();
	}

	void CCollisionDetection::SphereSphere(CSphere_Object* a, CSphere_Object* b)
	{
		const float distance = Distance(a->getPosition(),b->getPosition());
		ASSERT(distance > 0.00001f);
		const float sumRadius = (a->GetRadius() + b->GetRadius());
		if (distance < sumRadius)
		{
			Collision* c = new Collision();
			c->objectA = a;
			c->objectB = b;
			c->normal = Normalize(a->getPosition() - b->getPosition());
			c->penetration = sumRadius - distance;
			c->point = a->getPosition() - c->normal * (a->GetRadius() - c->penetration*0.5f);
			_collisions.push_back(c);
		}
	}

	void CCollisionDetection::SphereCuboid(CSphere_Object* a, CCube_Object* b)
	{
		//printf("SphereCuboid!\n");
	}

	void CCollisionDetection::SpherePlane(CSphere_Object* a, CPlane_Object* b)
	{
		//assumme all plane are flat for now
		const float distance = -1.0f*b->getPosition().y;

		//assume perfect sphere
		const float radius = a->GetRadius();

		float separation = Dot(a->getPosition(), b->GetNormal()) + distance;
		//ASSERT(separation > 0.00001f);

		if (isnan(separation))
		{
			separation = 0;
		}

		if (separation > radius)
		{
			return;
		}
		Collision* c = new Collision();
		c->objectA = a;
		c->objectB = b;
		c->normal = b->GetNormal();
		c->penetration = radius - separation;
		c->point = a->getPosition() - b->GetNormal() * separation;
		_collisions.push_back(c);
		return;

	}

	void CCollisionDetection::CuboidCuboid(CCube_Object* a, CCube_Object* b)
	{
		printf("CuboidCuboid!\n");
	}

	void CCollisionDetection::CuboidPlane(CCube_Object* a, CPlane_Object* b)
	{
	
		//local coords on cube
		Vector4 points[8] = { 
			Vector4(a->GetSize().x,	a->GetSize().y,		a->GetSize().z,	1.0f),
			Vector4(-a->GetSize().x, a->GetSize().y, a->GetSize().z, 1.0f),
			Vector4(a->GetSize().x, -a->GetSize().y, a->GetSize().z, 1.0f),
			Vector4(-a->GetSize().x, -a->GetSize().y, a->GetSize().z, 1.0f),
			Vector4(a->GetSize().x, a->GetSize().y, -a->GetSize().z, 1.0f),
			Vector4(-a->GetSize().x, a->GetSize().y, -a->GetSize().z, 1.0f),
			Vector4(a->GetSize().x, -a->GetSize().y, -a->GetSize().z, 1.0f),
			Vector4(-a->GetSize().x, -a->GetSize().y, -a->GetSize().z, 1.0f)
		};

		//transfrom to global
		Matrix4 rot = EulerToMatrix(a->getRotation());
		Matrix4 trn = Translation(a->getPosition());
		for (int i = 0; i < 8;i++)
		{
			points[i] = trn * rot * points[i];
			//Engine::Renderer->DrawCross(Vector3(points[i]), 0.5f);
		}

		//For each point on the cube, which side of cube are they on?
		float distances[8];
		for (int i = 0; i < 8; i++)
		{
			Vector3 p = b->getPosition();
			Vector3 n = b->GetNormal();

			Vector3 t = (Vector3)points[i];

			distances[i] = Dot(p, n) - Dot(t, n);

			if (distances[i] > 0)
			{
				Collision* c = new Collision();
				c->objectA = a;
				c->objectB = b;
				c->normal = b->GetNormal();
				c->penetration = distances[i];
				c->point = t + n * c->penetration;
				_collisions.push_back(c);
			}
		}

	}

	void CCollisionDetection::PlanePlane(CPlane_Object* A, CPlane_Object* B)
	{
		printf("PlanePlane!\n");
	}


	///
	void CCollisionDetection::Resolve()
	{
		for (unsigned int i = 0; i < _collisions.size(); i++)
		{
			Collision* c = _collisions[i];
			Engine::Renderer->DrawCross(c->point, 0.5f);
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
				continue;
			}
			
			// NORMAL Impulse
			{
				// Coefficient of Restitution
				const float e = 0.5f;
				
				const float normDiv =
				Dot(c->normal, c->normal) * 
				((invMass0 + invMass1) + Dot( c->normal,
					Cross((Cross(r0, c->normal)*InvInertia0), r0)
					+ Cross( (Cross(r1, c->normal)* InvInertia1), r1)
				));

				ASSERT(normDiv > 0.0f);
				
				float jn = -1 * (1 + e)* Dot(dv, c->normal) / normDiv;
			
				// Hack fix to stop sinking
				// bias impulse proportional to penetration distance
				jn = jn + (c->penetration*1.5f);
				
				if (invMass0 != 0)
				{
					Vector3 impulse = invMass0 * c->normal * jn;
					objectA->AddImpulse(impulse);
					objectA->AddRotationImpulse(InvInertia0 * Cross(r0, c->normal * jn));
				}
				if (invMass1 != 0)
				{
					objectB->AddImpulse(-1.0f* invMass1 * c->normal * jn);
					objectB->AddRotationImpulse(-1.0f* Cross(r1, c->normal * jn) * InvInertia1);
				}
			}
			
			// TANGENT Impulse Code
			{
				// Work out our tangent vector , with is perpendicular
				// to our collision normal
				Vector3 tangent = Vector3(0, 0, 0);
				tangent = dv - (Dot(dv, c->normal) * c->normal);

				tangent = Normalize(tangent);
				ASSERT(!isnan(tangent.x) && !isnan(tangent.y) && !isnan(tangent.z));

				const float tangDiv = invMass0 + invMass1 + Dot(tangent, Cross((Cross(r0, tangent) * InvInertia0), r0) + Cross((Cross(r1, tangent) * InvInertia1), r1));
			
				const float jt = -1 * Dot(dv, tangent) / tangDiv;
				// Clamp min/max tangental component
				
				
				// Apply contact impulse
				if (invMass0 != 0)
				{
					Vector3 impulse = invMass0 * tangent * jt;
					ASSERT(!isnan(impulse.x) && !isnan(impulse.y) && !isnan(impulse.z));
					Vector3 rotImpulse = InvInertia0 * Cross(r0, tangent * jt);
					objectA->AddImpulse(impulse);
					objectA->AddRotationImpulse(rotImpulse);
				}
				if (invMass1 != 1)
				{
					Vector3 impulse = invMass1 * tangent * jt;
					Vector3 rotImpulse = Cross(r1, tangent * jt) *  InvInertia1;
					objectB->AddImpulse(-1.0f * impulse);
					objectB->AddRotationImpulse(-1.0f* rotImpulse);
				}
			} // TANGENT
			
			
			delete c;
		}
		_collisions.clear();
	}

}