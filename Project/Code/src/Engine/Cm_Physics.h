#pragma once
#include "Component.h"
#include "Maths.h"

namespace Engine{
	class CPhysicsObject;
	class CmPhysics : public CComponent{

	protected:
		bool _showdebug;
		CPhysicsObject* _po;
		CmPhysics(std::string s);
	public:
		~CmPhysics();

		void Render();
		void Update(double delta);

		float GetMass();
		void SetMass(float m);
		bool UsesGravity();
		void SetUsesGravity(bool b);
	};

	class CmPhysics_Cuboid : public CmPhysics{

	public:
		CmPhysics_Cuboid(float mass, Vector3 position,float lw, float lh, float ld);
		~CmPhysics_Cuboid();
	};

	class CmPhysics_Sphere : public CmPhysics{

	public:
		CmPhysics_Sphere(float mass, Vector3 position, float radius);
		~CmPhysics_Sphere();
	};

	class CmPhysics_Plane : public CmPhysics{

	public:
		CmPhysics_Plane(Vector3 position, Vector3 normal);
		~CmPhysics_Plane();
	};
}