#include "Physics_Objects_shapes.h"

namespace Physics{

	//---- Interia Tensors for each shape
	Matrix4 CCube_Object::CalculateInverseInertiaTensor()
	{
		if (_invMass == 0){
			return Matrix4(0.0f);
		}

		float x2 = 4.0f*(_size.getX()*_size.getX());
		float y2 = 4.0f*(_size.getY()*_size.getY());
		float z2 = 4.0f*(_size.getZ()*_size.getZ());

		float ix = (y2 + z2) / (_invMass * 12.0f);
		float iy = (x2 + z2) / (_invMass * 12.0f);
		float iz = (x2 + y2) / (_invMass * 12.0f);

		Matrix4 mat;
		mat[0][0] = 1.0f / ix;
		mat[1][1] = 1.0f / iy;
		mat[2][2] = 1.0f / iz;
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
		//_orientation = Normalize(Quaternion(2.0f,0,0,9.0f));
		_size = Vector3(lw, lh, ld);
		SetMass(mass);
	}

	CSphere_Object::CSphere_Object(const float mass, const Vector3& position, const  Quaternion& rotation, const float radius) : CPhysicsObject(mass, position, rotation)
	{
		type = SPHERE;
		_radius = radius;
		SetMass(mass);
	}

	CPlane_Object::CPlane_Object(const Vector3& position, const Vector3& normal) : CPhysicsObject(0.0f, position, Quaternion::identity())
	{
		type = PLANE;
		_normal = normal;
		SetMass(0);
	}

	//---- Debug lines

	std::vector<Vector3> CCube_Object::getDebugLines()
	{
		std::vector<Vector3> aa(4);
		aa.push_back(_position + Vector3(_size.getX(), _size.getY(), _size.getZ()));
		aa.push_back(_position + Vector3(-_size.getX(), -_size.getY(), -_size.getZ()));
		aa.push_back(_position + Vector3(-_size.getX(), _size.getY(),-_size.getZ()));
		aa.push_back(_position + Vector3(_size.getX(), -_size.getY(), _size.getZ()));
		aa.push_back(_position + Vector3(_size.getX(), _size.getY(), -_size.getZ()));
		aa.push_back(_position + Vector3(-_size.getX(), -_size.getY(), _size.getZ()));
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