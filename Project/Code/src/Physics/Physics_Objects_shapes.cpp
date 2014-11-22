#include "Physics_Objects_shapes.h"

namespace Physics{

	//---- Interia Tensors for each shape
	Matrix4 CCube_Object::CalculateInverseInertiaTensor()
	{
		if (_invMass == 0){
			return Matrix4(0.0f);
		}

		float width =	1.0f*(_size.x*_size.x);
		float height =	1.0f*(_size.y*_size.y);
		float depth =	1.0f*(_size.z*_size.z);

		Matrix4 mat;
		mat[1][1] = (_invMass * 12.0f)* (height + depth);
		mat[2][2] = (_invMass * 12.0f)* (width + depth);
		mat[0][0] = (_invMass * 12.0f)* (width + height);
		mat[3][3] = 1.0f;
		return mat;
	}

	Matrix4 CSphere_Object::CalculateInverseInertiaTensor()
	{
		if (_invMass == 0){
			return Matrix4(0.0f);
		}

		float f = (1.0f/_invMass)  * _radius* _radius * (2.0f / 5.0f);
		Matrix4 mat;
		mat[0][0] = f;
		mat[1][1] = f;
		mat[2][2] = f;
		mat[3][3] = 1.0f;
		return mat;
	}

	Matrix4 CPlane_Object::CalculateInverseInertiaTensor()
	{
		return Matrix4(0.0f);
		//return Matrix3(1.0f);
	}

	//---- shape constructors

	CCube_Object::CCube_Object(const float mass, const Vector3& position, const  Quaternion& rotation, const float lw, const float lh, const float ld) :CPhysicsObject(mass, position, rotation)
	{
		type = CUBEOID;
		_size = Vector3(lw, lh, ld);
		SetMass(mass);
	}

	CSphere_Object::CSphere_Object(const float mass, const Vector3& position, const  Quaternion& rotation, const float radius) : CPhysicsObject(mass, position, rotation)
	{
		type = SPHERE;
		_radius = radius;
		SetMass(mass);
	}

	CPlane_Object::CPlane_Object(const Vector3& position, const Vector3& normal) : CPhysicsObject(0.0f, position, Quaternion(0,0,0,1.0f))
	{
		type = PLANE;
		_normal = normal;
		SetMass(0);
	}

	//---- Debug lines

	std::vector<Vector3> CCube_Object::getDebugLines()
	{
		std::vector<Vector3> aa(4);
		aa.push_back(_position + Vector3(_size.x, _size.y, _size.z));
		aa.push_back(_position + Vector3(-_size.x, -_size.y, -_size.z));
		aa.push_back(_position + Vector3(-_size.x, _size.y,-_size.z));
		aa.push_back(_position + Vector3(_size.x, -_size.y, _size.z));
		aa.push_back(_position + Vector3(_size.x, _size.y, -_size.z));
		aa.push_back(_position + Vector3(-_size.x, -_size.y, _size.z));
		return aa;
	}
	std::vector<Vector3> CSphere_Object::getDebugLines()
	{
		std::vector<Vector3> aa(0);
		return aa;
	}
	std::vector<Vector3> CPlane_Object::getDebugLines()
	{
		std::vector<Vector3> aa(4);
		aa.push_back(_position + Vector3(-100, 0, 0));
		aa.push_back(_position + Vector3(100, 0, 0));
		aa.push_back(_position + Vector3(0, 0, -100));
		aa.push_back(_position + Vector3(0, 0, 100));
		return aa;
	}

}