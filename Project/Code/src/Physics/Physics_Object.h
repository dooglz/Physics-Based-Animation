#pragma once
#include "../Engine/Maths.h"

namespace Physics{
	class CPhysicsObject
	{
	public:

		struct State
		{

			///
			Vector3 forces;
			Vector3 torques;
			/// primary physics state

			Vector3 position;               // the position of the cube center of mass in world coordinates (meters).
			Vector3 momentum;               // the momentum of the cube in kilogram meters per second.
			Quaternion orientation;         // the orientation of the cube represented by a unit quaternion.
			Vector3 angularMomentum;        // angular momentum vector.

			// secondary state

			Vector3 velocity;               // velocity in meters per second (calculated from momentum).
			Quaternion spin;                // quaternion rate of change in orientation.
			Vector3 angularVelocity;        // angular velocity (calculated from angularMomentum).

			/// constant state
			float size;                     // length of the cube sides in meters.
			float mass;                     // mass of the cube in kilograms.
			float inverseMass;              // inverse of the mass used to convert momentum to velocity.
			float inertiaTensor;            // inertia tensor of the cube (i have simplified it to a single value due to the mass properties a cube).
			float inverseInertiaTensor;     // inverse inertia tensor used to convert angular momentum to angular velocity.

			/// Recalculate secondary state values from primary values.
			void recalculate()
			{
				velocity = momentum * inverseMass;
				angularVelocity = angularMomentum * inverseInertiaTensor;
				Normalize(orientation);
				spin = 0.5f * Quaternion(0, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
			}
		};

	protected:

		struct Derivative
		{
			Vector3 velocity;	// velocity is the derivative of position.
			Vector3 force;		// force in the derivative of momentum.
			Quaternion spin;	// spin is the derivative of the orientation quaternion.
			Vector3 torque;		// torque is the derivative of angular momentum.
		};

		State _previous;		// previous physics state.
		State _current;		// current physics state.

		static Derivative evaluate(const State &state, float t);
		static Derivative evaluate(State state, float t, float dt, const Derivative &derivative);
		static void integrate(State &state, float t, float dt);

	public:
		CPhysicsObject();
		Vector3 getPosition();
		Vector3 getRotation();
		void AddForce(Vector3 v);
		void AddTorque(Vector3 v);
		void AddImpulse(Vector3 v);
		void Update(float t, float timestep);
	};
}