#include "Physics_Object.h"
#include "Physics.h"
#include "../Engine/Utilities.h"
#include "SpacePartition.h"

namespace Physics{

	CPhysicsObject::CPhysicsObject(const float mass, const Vector3& position, const  Quaternion& rotation)
	{
		printf("Hello, I'm a new physics object, m:%f, pos:(%f,%f,%f)\n", mass, position.getX(), position.getY(), position.getZ());
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

		//keep everything contained
		if (_position.getX() * _position.getX() > 3600.0f){
			AddImpulse(Vector3(-1.9f*_linVelocity.getX(), 0, 0));
		}
		if (_position.getZ() * _position.getZ() > 3600.0f){
			AddImpulse(Vector3(0,0,-1.9f*_linVelocity.getZ()));
		}
		if (_position.getY() * _position.getY() > 3600.0f){
			AddImpulse(Vector3(0,-1.9f*_linVelocity.getY(),0));
		}
		
		if (_position.getX() * _position.getX() < 28.0f && _position.getZ() * _position.getZ() < 28.0f &&  _position.getY() < 8.0f)
		{
			AddImpulse(Vector3(0.015f*_linVelocity.getX(), 0.05f, 0.0015f*_linVelocity.getZ()));
		}


		// Add Gravity
		if (usesGravity){
			AddForce(_position, Vector3(0, -9.8f * (1.0f / _invMass), 0));
			//AddRotationImpulse(Vector3(0, 0.01f, 0));
		//	AddForce(_position+Vector3(1.0f,0,0), Vector3(0, 0.01f, 0));
		}

		// Update Linear
		_linVelocity += ((_forces * _invMass) * dtf);
		_position += (_linVelocity * dtf);
		_forces = Vector3(0, 0, 0);

		// Update Angular
		_angVelocity += V4toV3(((_worldInvInertia * Vector4(_torques,0)) * dtf));
		Quaternion Qvel = (Quaternion(0, _angVelocity.getX(), _angVelocity.getY(), _angVelocity.getZ()) * 0.5f) * _orientation;
		_orientation += Qvel * dtf;

		_orientation = Normalize(_orientation);
		_torques = Vector3(0, 0, 0);

		//damping
		_angVelocity *= 0.999f;
		_linVelocity *= 0.999f;

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
		_torques += Cross((p - _position), f);
	}

	void CPhysicsObject::AddTorque(const Vector3& v)
	{
		if (_invMass <= 0.0f) return;
		_torques += v;
	}

	void CPhysicsObject::AddImpulse(const Vector3& v)
	{
		ASSERT(!isnan(v.getX()) && !isnan(v.getY()) && !isnan(v.getZ()));
		_linVelocity += v;
	}

	void CPhysicsObject::AddRotationImpulse(const Vector3& v)
	{
		ASSERT(!isnan(v.getX()) && !isnan(v.getY()) && !isnan(v.getZ()));
		_angVelocity += v;
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