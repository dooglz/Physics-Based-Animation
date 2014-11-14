#include "Physics_Object.h"
#include "Physics.h"

namespace Physics{

	CPhysicsObject::CPhysicsObject(float mass, Vector3 position)
	{
		printf("Hello, I'm a new physics object, m:%f\n",mass);
		System->_scene.push_back(this);
		_current.mass = mass;
		_current.position = position;
		if (mass == 0.0f){
			_current.inverseMass = 0.0f;
		}
		else
		{
			_current.inverseMass = 1.0f / _current.mass;
		}
		_current.momentum = Vector3(0, 0, 0);
		//_current.orientation = Quaternion(0.0f);
		_current.angularMomentum = Vector3(0, 0, 0);
	}

	void CPhysicsObject::Update(double t, double timestep)
	{
		_previous = _current;
		if (_current.mass = 0){ 
			return; 
		}
		integrate(_current, t, timestep);
		_current.forces = Vector3(0.0f);
		_current.torques = Vector3(0.0f);
		if (usesGravity){ _current.forces += System->gavity; }
	}

	Vector3 CPhysicsObject::getPosition()
	{
		return _current.position;
	}

	Vector3 CPhysicsObject::getRotation()
	{
		return QuatToEuler(_current.orientation);
	}

	float CPhysicsObject::GetMass()
	{
		return _current.mass;
	}

	void CPhysicsObject::SetMass(float m)
	{
		_current.mass = m;
		_current.inverseMass = 1.0f / _current.mass;
		_current.inertiaTensor = CalculateInertiaTensor();
		_current.inverseInertiaTensor = Inverse(_current.inertiaTensor);
		_current.recalculate();
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


	CPhysicsObject::Derivative CPhysicsObject::evaluate(const CPhysicsObject::State &state, double t)
	{
		Derivative output;
		output.velocity = state.velocity;
		output.spin = state.spin;
		output.force += state.forces; //*t
		output.torque += state.torques;//*t
		return output;
	}

	CPhysicsObject::Derivative CPhysicsObject::evaluate(CPhysicsObject::State state, double t, double dt, const Derivative &derivative)
	{
		float fdt = (float)dt;
		state.position += derivative.velocity * fdt;
		state.momentum += derivative.force * fdt;
		state.orientation += derivative.spin * fdt;
		state.angularMomentum += derivative.torque * fdt;
		state.recalculate();

		Derivative output;
		output.velocity = state.velocity;
		output.spin = state.spin;
		output.force += state.forces; //*t
		output.torque += state.torques;//*t
		return output;
	}

	void CPhysicsObject::integrate(State &state, double t, double dt)
	{
		float fdt = (float)dt;
		Derivative a = evaluate(state, t);
		Derivative b = evaluate(state, t, dt*0.5f, a);
		Derivative c = evaluate(state, t, dt*0.5f, b);
		Derivative d = evaluate(state, t, dt, c);

		state.position += 1.0f / 6.0f * fdt * (a.velocity + 2.0f*(b.velocity + c.velocity) + d.velocity);
		state.momentum += 1.0f / 6.0f * fdt * (a.force + 2.0f*(b.force + c.force) + d.force);
		state.orientation += 1.0f / 6.0f * fdt * (a.spin + 2.0f*(b.spin + c.spin) + d.spin);
		state.angularMomentum += 1.0f / 6.0f * fdt * (a.torque + 2.0f*(b.torque + c.torque) + d.torque);

		state.recalculate();
	}
}