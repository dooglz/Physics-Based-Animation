#include "Physics_Object.h"
#include "Physics.h"
#include "../Engine/Utilities.h"

namespace Physics{


	Matrix3 CPhysicsObject::State::GetInvWorldTensor()
	{	
		return inverseInertiaTensor * QuatToMatrix3(orientation);
		//return QuatToMatrix3(orientation) * inverseInertiaTensor;
		//return QuatToMatrix3(Normalize(orientation)) * inverseInertiaTensor * Inverse(QuatToMatrix3(Normalize(orientation)));
		//return Inverse(QuatToMatrix3(Normalize(orientation))) * inverseInertiaTensor * QuatToMatrix3(Normalize(orientation));
	}

	void CPhysicsObject::State::SetTensor(Matrix3 t)
	{
		inertiaTensor = t;
		if (t[0][0] || t[1][1] || t[2][2]){
			inverseInertiaTensor = Inverse(inertiaTensor);
		}else{
			inverseInertiaTensor = Matrix3(0.0f);
		}
	}

	CPhysicsObject::CPhysicsObject(float mass, Vector3 position)
	{
		printf("Hello, I'm a new physics object, m:%f\n",mass);
		System->_scene.push_back(this);
		_current.mass = mass;
		_current.position = position;
		if (mass == 0.0f){
			_current.inverseMass = 0.0f;
		}else{
			_current.inverseMass = 1.0f / _current.mass;
		}
		_current.momentum = Vector3(0, 0, 0);
		//_current.orientation = Normalize(Quaternion(0.9f,0,0,0.2f));
		_current.angularMomentum = Vector3(0, 0, 0);
		//_current.torques += Vector3(25.1f, 10.0f, 50.0f);
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
		//	_current.torques += Vector3(0, 1.0f, 0);
		}
		//_current.velocity *= 0.9999f;
		//_current.angularVelocity *= 0.9999f;
	}

	void CPhysicsObject::SetMass(float m)
	{
		_current.mass = m;
		_current.inverseMass = 1.0f / _current.mass;
		_current.SetTensor(CalculateInertiaTensor());
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
		
		ASSERT(!isnan(v.x) && !isnan(v.y) && !isnan(v.z));
		Vector3 targetSpeed = (_current.velocity + v);
		Vector3 diff = targetSpeed - _current.velocity;
		Vector3 Acceleration = diff / 0.01f;
		Vector3 force = _current.mass *  Acceleration;
		AddForce(force);
		
		//_current.velocity += v;
		//_current.momentum = _current.velocity * _current.mass;
		//_current.momentum = Vector3(0);
	}

	void CPhysicsObject::AddRotationImpulse(Vector3 v)
	{
		
		ASSERT(!isnan(v.x) && !isnan(v.y) && !isnan(v.z));
		Vector3 targetSpeed = (_current.angularVelocity + v);
		Vector3 diff = targetSpeed - _current.angularVelocity;
		Vector3 Acceleration = diff / 0.01f;
		Vector3 force = Acceleration * (_current.GetInvWorldTensor());
		
		AddTorque(force);
		
		//_current.angularVelocity += v;
		//_current.angularMomentum = _current.angularVelocity * _current.GetInvLocalTensor();
	}

	void CPhysicsObject::State::recalculate()
	{
		velocity = momentum * inverseMass;
		angularVelocity = angularMomentum * GetInvWorldTensor();
		Normalize(orientation);
		spin = 0.5f * Quaternion(0, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
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

	Matrix3 CPhysicsObject::GetInvLocalTensor()
	{
		return _current.GetInvLocalTensor();
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

	Vector3 CPhysicsObject::GetLinearVeloicty()
	{
		return _current.velocity;
	}

	Vector3 CPhysicsObject::GetAngularVeloicty()
	{
		return _current.angularVelocity;
	}

	Quaternion CPhysicsObject::getRotationQ()
	{
		return _current.orientation;
	}

	Matrix3 CPhysicsObject::GetInvWorldTensor()
	{
		return _current.GetInvWorldTensor();
	}

	void CPhysicsObject::setTensor(Matrix3 t)
	{
		_current.SetTensor(t);
	}

	Matrix3 CPhysicsObject::State::GetLocalTensor()
	{
		return inertiaTensor;
	}

	Matrix3 CPhysicsObject::State::GetInvLocalTensor()
	{
		return inverseInertiaTensor;
	}
}