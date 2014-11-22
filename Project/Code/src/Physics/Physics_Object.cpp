#include "Physics_Object.h"
#include "Physics.h"
#include "../Engine/Utilities.h"

namespace Physics{

	CPhysicsObject::CPhysicsObject(const float mass, const Vector3& position, const  Quaternion& rotation)
	{
		printf("Hello, I'm a new physics object, m:%f, pos:(%f,%f%,%f)\n", mass, position.x, position.y, position.z);
		System->_scene.push_back(this);
		_position = position;
		_orientation = rotation;
		_linVelocity = Vector3(0, 0, 0);
		_angVelocity = Vector3(0, 0, 0);
		_torques = Vector3(0, 0, 0);
		_forces = Vector3(0, 0, 0);
		//SetMass(mass);
		//_torques += Vector3(25.1f, 10.0f, 50.0f);
	}

	void CPhysicsObject::Integrate(const double dt, const double timestep)
	{
		float dtf = (float)timestep;
		UpdateMatrix();
		if (_invMass == 0.0f){
			return;
		}

		// Add Gravity
		if (usesGravity){
			AddForce(_position, Vector3(0, -9.8f * (1.0f / _invMass), 0));
			//AddForce(_position, Vector3(0, 0, 0));
		}

		// Update Linear
		_linVelocity += ((_forces * _invMass) * dtf);
		_position += (_linVelocity * dtf);
		_forces = Vector3(0, 0, 0);

		// Update Angular
		_angVelocity += Vector3(((_worldInvInertia * Vector4(_torques,0)) * dtf));
		Quaternion Qvel = (Quaternion(_angVelocity.x, _angVelocity.y, _angVelocity.z, 0) * 0.5f) * _orientation;
		_orientation += Qvel * dtf;

		_orientation = Normalize(_orientation);
		_torques = Vector3(0, 0, 0);

		UpdateMatrix();
	}

	void CPhysicsObject::UpdateMatrix()
	{
		Matrix4 matR = QuatToMatrix(_orientation);
		Matrix4 matT = Translation(_position);
		_matWorld = matR * matT;	
		_worldInvInertia = Transpose(matR) * _localInvInertia * matR;
		/*
		_localxyz[0] = Matrix4::Transform(matR, Vector3(1, 0, 0));
		_localxyz[1] = Matrix4::Transform(matR, Vector3(0, 1, 0));
		_localxyz[2] = Matrix4::Transform(matR, Vector3(0, 0, 1));
		*/
	}

	void CPhysicsObject::SetMass(const float m)
	{
		if (m == 0.0f){
			_invMass = 0.0f;
		}
		else{
			_invMass = 1.0f / m;
		}
		_localInvInertia = CalculateInverseInertiaTensor();
		UpdateMatrix();
	}

	void CPhysicsObject::AddForce(const Vector3& p, const  Vector3& f)
	{
		if (_invMass <= 0.0f) return;
		_forces += f;
//		_torques += Cross((p - _position), f);
	}

	void CPhysicsObject::AddTorque(const Vector3& v)
	{
		if (_invMass <= 0.0f) return;
		_torques += v;
	}

	void CPhysicsObject::AddImpulse(const Vector3& v)
	{
		ASSERT(!isnan(v.x) && !isnan(v.y) && !isnan(v.z));
		_linVelocity += v;
		//_current.momentum = _current.velocity * _current.mass;
		//_current.momentum = Vector3(0);
	}

	void CPhysicsObject::AddRotationImpulse(const Vector3& v)
	{
		ASSERT(!isnan(v.x) && !isnan(v.y) && !isnan(v.z));

		_angVelocity += v;
		//_current.angularMomentum = _current.angularVelocity * _current.GetInvLocalTensor();
	}


	Matrix4 CPhysicsObject::GetInvLocalTensor() const
	{
		return _localInvInertia;
	}

	Vector3 CPhysicsObject::GetPosition() const
	{
		return _position;
	}

	float CPhysicsObject::GetInvMass() const
	{
		return _invMass;
	}

	float CPhysicsObject::GetMass() const
	{
		if (_invMass == 0.0f){
			return 0;
		}
		return (1.0f/_invMass);
	}

	Vector3 CPhysicsObject::GetLinearVeloicty() const
	{
		return _linVelocity;
	}

	Vector3 CPhysicsObject::GetAngularVeloicty() const
	{
		return _angVelocity;
	}

	Quaternion CPhysicsObject::GetOrientation() const
	{
		return _orientation;
	}

	Matrix4 CPhysicsObject::GetInvWorldTensor() const
	{
		return _worldInvInertia;
	}
}