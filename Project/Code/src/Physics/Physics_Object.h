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

	public:
		void UpdateMatrix();
		void Integrate(double dt, double timestep);
		virtual std::vector<Vector3> getDebugLines() = 0;
		CPhysicsObject(float mass, const Vector3& position, const  Quaternion& rotation);

		//
		void AddForce(Vector3& v, Vector3& p);
		void AddTorque(Vector3 v);
		void AddImpulse(Vector3 v);
		void AddRotationImpulse(Vector3 v);

		//getters and setters
		Vector3 GetPosition();
		Quaternion GetOrientation();
		Vector3 GetLinearVeloicty();
		Vector3 GetAngularVeloicty();
		Matrix4 GetInvWorldTensor();
		Matrix4 GetInvLocalTensor();
		float GetMass();
		float GetInvMass();
		void SetMass(float m);
	};
}