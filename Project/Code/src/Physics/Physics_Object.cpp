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
		_current.torques += Vector3(0, 1.1f, 1.5f);
	}

	void CPhysicsObject::Update(double t, double timestep)
	{
		_previous = _current;
		if (_current.mass == 0.0f){ 
			return; 
		}

		integrate(_current, t, timestep);
		_current.forces = Vector3(0.0f);
		_current.torques = Vector3(0.0f);
		if (usesGravity){
			_current.forces += System->gavity; 
		//	_current.forces += Vector3(5.1f,0, 0);
		}
		//dampening
		_current.velocity *= 0.9999f;
		_current.angularVelocity *= 0.9999f;
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

	float CPhysicsObject::GetInvMass()
	{
		return _current.inverseMass;
	}

	Matrix3 CPhysicsObject::GetInvTensor()
	{
		return _current.inverseInertiaTensor;
	}

	Matrix3 CPhysicsObject::GetTensor()
	{
		return _current.inertiaTensor;
	}

	Vector3 CPhysicsObject::GetLinearVeloicty()
	{
		return _current.velocity;
	}

	Vector3 CPhysicsObject::GetAngularVeloicty()
	{
		return _current.angularVelocity;
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
		_current.velocity += v;
		_current.momentum = _current.velocity * _current.mass;
	}

	void CPhysicsObject::AddRotationImpulse(Vector3 v)
	{
		_current.angularVelocity += v;
		_current.angularMomentum = _current.angularVelocity * _current.inverseInertiaTensor;
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