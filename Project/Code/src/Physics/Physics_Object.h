#pragma once
#include "../Engine/Maths.h"
#include <vector>

namespace Physics{
	class CPhysicsObject
	{
	public:
		enum shapeType { CUBEOID, SPHERE, PLANE };
		shapeType type;
		bool usesGravity;

	protected:
		virtual Matrix4 CalculateInverseInertiaTensor() = 0;

		// Basic rigid body variables
		// ***** LINEAR ******
		Vector3		_position;		// centre of mass
		float		_invMass;
		Vector3		_linVelocity;
		Vector3		_forces;

		// ***** ANGULAR******
		Quaternion	_orientation;
		Matrix4		_localInvInertia;
		Vector3		_angVelocity;
		Vector3		_torques;

		// Custom optimisation paramaters
		Matrix4		_matWorld;
		Matrix4		_worldInvInertia;
		~CPhysicsObject(){};

	public:
		void UpdateMatrix();
		void Integrate(const double dt, const double timestep);
		virtual std::vector<Vector3> getDebugLines() = 0;
		CPhysicsObject(const float mass, const Vector3& position, const  Quaternion& rotation);

		//
		void AddForce(const Vector3& v, const Vector3& p);
		void AddTorque(const Vector3& v);
		void AddImpulse(const Vector3& v);
		void AddRotationImpulse(const Vector3& v);

		//getters and setters
		Vector3 GetPosition() const;
		Quaternion GetOrientation() const;
		Vector3 GetLinearVeloicty() const;
		Vector3 GetAngularVeloicty() const;
		Matrix4 GetInvWorldTensor() const;
		Matrix4 GetInvLocalTensor() const;
		float GetMass() const;
		float GetInvMass() const;
		void SetMass(const float m);
	};
}