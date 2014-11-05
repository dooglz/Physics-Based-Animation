#include "Physics_Object.h"
#include "Physics.h"

namespace Physics{

	CPhysicsObject::CPhysicsObject()
	{
		printf("Hello, I'm a new physics object\n");
		System->_scene.push_back(this);
		_current.size = 1;
		_current.mass = 1;
		_current.inverseMass = 1.0f / _current.mass;
		_current.position = Vector3(0, 1, 0);
		_current.momentum = Vector3(0, 0, 0);
		//_current.orientation = Quaternion(0.0f);
		_current.angularMomentum = Vector3(0, 0, 0);
		_current.inertiaTensor = _current.mass * _current.size * _current.size * 1.0f / 6.0f;
		_current.inverseInertiaTensor = 1.0f / _current.inertiaTensor;
		_current.recalculate();
		_previous = _current;
	}


	void CPhysicsObject::Update(float t, float timestep)
	{
		_previous = _current;
		integrate(_current, t, timestep);
		_current.forces = Vector3(0.0f);
		_current.torques = Vector3(0.0f);
	}

	Vector3 CPhysicsObject::getPosition()
	{
		return _previous.position;
	}

	Vector3 CPhysicsObject::getRotation()
	{
		return QuatToEuler(_previous.orientation);
	}

	void CPhysicsObject::AddForce(Vector3 v)
	{
		_current.forces += v;
	}
	
	void CPhysicsObject::AddTorque(Vector3 v)
	{
		_current.torques += v;
	}
	
	void CPhysicsObject::AddImpulse(Vector3 v)
	{
		//todo 
		ASSERT(false);
	}


	CPhysicsObject::Derivative CPhysicsObject::evaluate(const CPhysicsObject::State &state, float t)
	{
		Derivative output;
		output.velocity = state.velocity;
		output.spin = state.spin;
		output.force += state.forces; //*t
		output.torque += state.torques;//*t
		return output;
	}

	CPhysicsObject::Derivative CPhysicsObject::evaluate(CPhysicsObject::State state, float t, float dt, const Derivative &derivative)
	{
		state.position += derivative.velocity * dt;
		state.momentum += derivative.force * dt;
		state.orientation += derivative.spin * dt;
		state.angularMomentum += derivative.torque * dt;
		state.recalculate();

		Derivative output;
		output.velocity = state.velocity;
		output.spin = state.spin;
		output.force += state.forces; //*t
		output.torque += state.torques;//*t
		return output;
	}

	void CPhysicsObject::integrate(State &state, float t, float dt)
	{
		Derivative a = evaluate(state, t);
		Derivative b = evaluate(state, t, dt*0.5f, a);
		Derivative c = evaluate(state, t, dt*0.5f, b);
		Derivative d = evaluate(state, t, dt, c);

		state.position += 1.0f / 6.0f * dt * (a.velocity + 2.0f*(b.velocity + c.velocity) + d.velocity);
		state.momentum += 1.0f / 6.0f * dt * (a.force + 2.0f*(b.force + c.force) + d.force);
		state.orientation += 1.0f / 6.0f * dt * (a.spin + 2.0f*(b.spin + c.spin) + d.spin);
		state.angularMomentum += 1.0f / 6.0f * dt * (a.torque + 2.0f*(b.torque + c.torque) + d.torque);

		state.recalculate();
	}
}