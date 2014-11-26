#include "Collision_Detection.h"
#include "../Engine/Renderer.h"
#include "../Engine/Utilities.h"

namespace Physics{
	std::vector<CCollisionDetection::Collision*> CCollisionDetection::_collisions;
	
	void CCollisionDetection::Scan(const std::vector<CPhysicsObject*>& scene)
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
						SphereSphere(static_cast<CSphere_Object*>(objA), static_cast<CSphere_Object*>(objB),true);
					}
					else if (objB->type == CPhysicsObject::CUBEOID)
					{
						SphereCuboid(static_cast<CSphere_Object*>(objA), static_cast<CCube_Object*>(objB), true);
					}
					else if (objB->type == CPhysicsObject::PLANE)
					{
						SpherePlane(static_cast<CSphere_Object*>(objA), static_cast<CPlane_Object*>(objB), true);
					}
				}
				else if(objA->type == CPhysicsObject::CUBEOID)
				{
					if (objB->type == CPhysicsObject::SPHERE)
					{
						SphereCuboid(static_cast<CSphere_Object*>(objB), static_cast<CCube_Object*>(objA), true);
					}
					else if (objB->type == CPhysicsObject::CUBEOID)
					{
						CuboidCuboid(static_cast<CCube_Object*>(objA), static_cast<CCube_Object*>(objB), true);
					}
					else if (objB->type == CPhysicsObject::PLANE)
					{
						CuboidPlane(static_cast<CCube_Object*>(objA), static_cast<CPlane_Object*>(objB), true);
					}
				}
				else if (objA->type == CPhysicsObject::PLANE)
				{
					if (objB->type == CPhysicsObject::SPHERE)
					{
						SpherePlane(static_cast<CSphere_Object*>(objB), static_cast<CPlane_Object*>(objA), true);
					}
					else if (objB->type == CPhysicsObject::CUBEOID)
					{
						CuboidPlane(static_cast<CCube_Object*>(objB), static_cast<CPlane_Object*>(objA), true);
					}
					else if (objB->type == CPhysicsObject::PLANE)
					{
						PlanePlane(static_cast<CPlane_Object*>(objA), static_cast<CPlane_Object*>(objB), true);
					}
				}
			}
		}
		Resolve();
	}

	bool CCollisionDetection::SphereSphere(CSphere_Object*const  a, CSphere_Object*const b, const bool resolve)
	{
		//return false;
		float distance = Distance2(a->GetPosition(),b->GetPosition());
		ASSERT(distance > 0.00001f);

		const float sumRadius = (a->GetRadius() + b->GetRadius());
		if (distance < (sumRadius * sumRadius))
		{
			if (resolve)
			{
				distance = sqrt(distance);
				Collision* c = new Collision(
					a, b,	//Objects 
					Normalize(a->GetPosition() - b->GetPosition()), //Collsion Normal
					a->GetPosition() - (Normalize(a->GetPosition() - b->GetPosition())) * (a->GetRadius() - (sumRadius - distance)*0.5f), //Point
					sumRadius - distance	//Penentration
					);
				_collisions.push_back(c);
			}
			return true;
		}
		return false;
	}

	bool CCollisionDetection::SphereCuboid(CSphere_Object* const a,CCube_Object* const b, const bool resolve)
	{
		return false;
		// Clamp each coordinate to the cuboid
		//
		//WE need ot take roation into accout here, for realtive position to really work
		Matrix4 rot = QuatToMatrix(b->GetOrientation());
		Matrix4 trn = Translation(b->GetPosition());
		Matrix4 inv = Inverse(trn * rot);
		Vector4 v4 = Vector4(a->GetPosition(), 1);

		//Vector3 realativePosition = a->getPosition() - b->getPosition();
		v4 = inv * v4;
		Vector3 realativePosition = V4toV3(v4);

		Vector3 closestPoint(
			Clamp(realativePosition.getX(), (1.0f*b->GetSize().getX())),
			Clamp(realativePosition.getY(), (1.0f*b->GetSize().getY())),
			Clamp(realativePosition.getZ(), (1.0f*b->GetSize().getZ()))
		);

		Vector3 closestPointWorld = V4toV3(trn * rot * Vector4(closestPoint, 1));

		// Check we're in contact
		float distance = Length(closestPoint - realativePosition);
		if (distance > a->GetRadius()) {
			return false;
		}
		//printf("SphereCuboid!\n");
		if (resolve)
		{
			Collision* c = new Collision(
				a, b,	//Objects 
				-Normalize(closestPointWorld - a->GetPosition()), //Collsion Normal
				closestPoint + b->GetPosition(), //Point
				a->GetRadius() - distance	//Penentration
				);
			_collisions.push_back(c);
		}
		return true;
	}

	bool CCollisionDetection::SpherePlane(CSphere_Object* const a,CPlane_Object* const b, const bool resolve)
	{
		//assumme all plane are flat for now
		const float distance = -1.0f*b->GetPosition().getY();

		//assume perfect sphere
		const float radius = a->GetRadius();

		float separation = Dot(a->GetPosition(), b->GetNormal()) + distance;
		//ASSERT(separation > 0.00001f);

		if (isnan(separation))
		{
			separation = 0;
		}

		if (separation < radius)
		{
			
			if (resolve)
			{
				Collision* c = new Collision(
					a, b,	//Objects 
					b->GetNormal(), //Collsion Normal
					a->GetPosition() - b->GetNormal() * separation, //Point
					radius - separation	//Penentration
					);
				_collisions.push_back(c);
			}
			return true;
		}

		return false;
	}

	bool CCollisionDetection::CuboidCuboid(CCube_Object* const a, CCube_Object* const b, const bool resolve)
	{
		printf("CuboidCuboid!\n");
		return false;
	}

	bool CCollisionDetection::CuboidPlane(CCube_Object* const a, CPlane_Object* const b, bool resolve)
	{
	
		//local coords on cube
		Vector4 points[8] = { 
			Vector4(a->GetSize().getX(),	a->GetSize().getY(),		a->GetSize().getZ(),	1.0f),
			Vector4(-a->GetSize().getX(), a->GetSize().getY(), a->GetSize().getZ(), 1.0f),
			Vector4(a->GetSize().getX(), -a->GetSize().getY(), a->GetSize().getZ(), 1.0f),
			Vector4(-a->GetSize().getX(), -a->GetSize().getY(), a->GetSize().getZ(), 1.0f),
			Vector4(a->GetSize().getX(), a->GetSize().getY(), -a->GetSize().getZ(), 1.0f),
			Vector4(-a->GetSize().getX(), a->GetSize().getY(), -a->GetSize().getZ(), 1.0f),
			Vector4(a->GetSize().getX(), -a->GetSize().getY(), -a->GetSize().getZ(), 1.0f),
			Vector4(-a->GetSize().getX(), -a->GetSize().getY(), -a->GetSize().getZ(), 1.0f)
		};

		//transfrom to global
		Matrix4 rot = QuatToMatrix(a->GetOrientation());
		Matrix4 trn = Translation(a->GetPosition());
		for (int i = 0; i < 8;i++)
		{
			points[i] = trn * rot * points[i];
			//Engine::Renderer->DrawCross(Vector3(points[i]), 0.5f);
		}

		//For each point on the cube, which side of cube are they on?
		float distances[8];
		bool isCollided = false;
		for (int i = 0; i < 8; i++)
		{
			Vector3 p = b->GetPosition();
			Vector3 n = b->GetNormal();

			Vector3 t = V4toV3(points[i]);

			distances[i] = Dot(p, n) - Dot(t, n);

			if (distances[i] > 0)
			{
			//	printf("CuboidPlane!\n");
				if (resolve)
				{
					Collision* c = new Collision(
						a, b,	//Objects 
						b->GetNormal(), //Collsion Normal
						t + n * distances[i], //Point
						distances[i]	//Penentration
						);
					_collisions.push_back(c);
				}
				isCollided = true;
			}
		}
		return isCollided;

	}

	bool CCollisionDetection::PlanePlane(CPlane_Object* const A, CPlane_Object* const B, const bool resolve)
	{
		printf("PlanePlane!\n");
		return false;
	}

	

	///
	void CCollisionDetection::Resolve()
	{
		//for (int a = 0; a < 2; ++a)
		//printf("%i!\n", _collisions.size());
		for (unsigned int i = 0; i < _collisions.size(); i++)
		{
			Collision* c = _collisions[i];
			Engine::Renderer->DrawCross(c->point, 0.5f);
			Engine::Renderer->DrawLine(c->point, c->point + c->normal);
			CPhysicsObject* const  objectA = c->objectA;
			CPhysicsObject* const  objectB = c->objectB;
			// Some simple check code.
		
			const float invMass0 = objectA->GetInvMass();
			const float invMass1 = objectB->GetInvMass();
			const Matrix4 InvInertia0 = objectA->GetInvWorldTensor();
			const Matrix4 InvInertia1 = objectB->GetInvWorldTensor();
			
			// Both objects are non movable
			if ((invMass0 + invMass1) == 0.0) return;
			Vector3 r0 = c->point - objectA->GetPosition();
			Vector3 r1 = c->point - objectB->GetPosition();
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
				const float e = 1.0f;
		
				const float normDiv =	 //Vector3::Dot(normal, normal) * => should equal 1
					((invMass0 + invMass1) +
					Dot(c->normal,
					Cross(V4toV3((InvInertia0 * Vector4(Cross(r0, c->normal), 0))), r0) +
					Cross(V4toV3((InvInertia1 * Vector4(Cross(r1, c->normal), 0))), r1)));
				ASSERT(normDiv > 0.0f);
				if (normDiv <= 0.0f){
			//		return;
				}
				
				float jn = -1 * (1 + e)* Dot(dv, c->normal) / normDiv;
			
				// Hack fix to stop sinking
				// bias impulse proportional to penetration distance
				jn = jn + (c->penetration*1.5f);
				
				Vector3 imp = c->normal * jn * invMass0;
				Vector3 r = V4toV3(InvInertia0 * Vector4(Cross(r0, c->normal * jn), 0));
			//	Vector3 r2 = Vector3(r.getY(),r.getX(),r.getZ());

				objectA->AddImpulse(imp);
				objectA->AddRotationImpulse(r);

				objectB->AddImpulse(-1.0f* c->normal * jn * invMass1);
				objectB->AddRotationImpulse(-1.0f* V4toV3(InvInertia1 * Vector4(Cross(r1, c->normal * jn), 0)));
			}
			
			// TANGENT Impulse Code
			#if 1
			{
				// Work out our tangent vector , with is perpendicular
				// to our collision normal
				Vector3 tangent = Vector3(0, 0, 0);
				tangent = dv - (Dot(dv, c->normal) * c->normal);

				tangent = Normalize(tangent);
				ASSERT(!isnan(tangent.getX()) && !isnan(tangent.getY()) && !isnan(tangent.getZ()));

				const float tangDiv = invMass0 + invMass1 + 
					Dot(tangent, Cross(V4toV3(InvInertia0 * Vector4(Cross(r0, tangent), 0)), r0) +
					Cross(V4toV3(InvInertia1 * Vector4(Cross(r1, tangent), 0)), r1));
			
				const float jt = -1 * Dot(dv, tangent) / tangDiv;
				// Clamp min/max tangental component
				
				
				// Apply contact impulse
				if (invMass0 != 0)
				{
					Vector3 impulse = invMass0 * tangent * jt;
					ASSERT(!isnan(impulse.getX()) && !isnan(impulse.getY()) && !isnan(impulse.getZ()));
					Vector3 rotImpulse = V4toV3(InvInertia0 * Vector4(Cross(r0, tangent * jt), 0));
					objectA->AddImpulse(impulse);
					objectA->AddRotationImpulse(rotImpulse);
				}
				if (invMass1 != 1)
				{
					Vector3 impulse = invMass1 * tangent * jt;
					Vector3 rotImpulse = V4toV3(InvInertia1 * Vector4(Cross(r1, tangent * jt), 0));
					objectB->AddImpulse(-1.0f * impulse);
					objectB->AddRotationImpulse(-1.0f* rotImpulse);
				}
			}
			#endif// TANGENT
			
			//extern bool cleanup;
			//if (cleanup)
			delete c;
		}
		//extern bool cleanup;
		//if (cleanup)
		_collisions.clear();
	}

}

static bool cleanup = false;