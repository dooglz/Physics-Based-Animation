#include "Physics_Objects_shapes.h"

namespace Physics{

	Matrix3 CCube_Object::CalculateInertiaTensor()
	{
		float width =	1.0f*_size.x;
		float height =	1.0f*_size.z;
		float depth =	1.0f*_size.y;

		Matrix3 mat;
		mat[0][0] = (_current.mass / 12.0f)*(height*height + depth*depth);
		mat[1][1] = (_current.mass / 12.0f)*(width*width + depth*depth);
		mat[2][2] = (_current.mass / 12.0f)*(width*width + height*height);
		return mat;
	}

	std::vector<Vector3> CCube_Object::getDebugLines()
	{
		std::vector<Vector3> aa(4);
		aa.push_back(_current.position + Vector3(_size.x, _size.y, _size.z));
		aa.push_back(_current.position + Vector3(-_size.x, -_size.y, -_size.z));
		aa.push_back(_current.position + Vector3(-_size.x, _size.y,-_size.z));
		aa.push_back(_current.position + Vector3(_size.x, -_size.y, _size.z));
		aa.push_back(_current.position + Vector3(_size.x, _size.y, -_size.z));
		aa.push_back(_current.position + Vector3(-_size.x, -_size.y, _size.z));
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
		aa.push_back(_current.position + Vector3(-100, 0, 0));
		aa.push_back(_current.position + Vector3(100, 0, 0));
		aa.push_back(_current.position + Vector3(0, 0, -100));
		aa.push_back(_current.position + Vector3(0, 0, 100));
		return aa;
	}

	CCube_Object::CCube_Object(float mass, Vector3 position, float lw, float lh, float ld) :CPhysicsObject(mass, position)
	{
		type = CUBEOID;
		_size = Vector3(lw, lh, ld);
		_current.SetTensor (CalculateInertiaTensor());
		_current.recalculate();
		_current.orientation = Normalize(Quaternion(0.9f, 0, 0, 0.2f));
		_previous = _current;

	}

	Matrix3 CSphere_Object::CalculateInertiaTensor()
	{
		return Matrix3(_current.mass * _radius* _radius * (2.0f / 5.0f));

	}

	CSphere_Object::CSphere_Object(float mass, Vector3 position, float radius) :CPhysicsObject(mass, position)
	{
		type = SPHERE;
		_radius = radius;
		_current.SetTensor(CalculateInertiaTensor());
		_current.recalculate();
		_previous = _current;
	}

	CPlane_Object::CPlane_Object(Vector3 position, Vector3 normal) : CPhysicsObject(0.0f, position)
	{
		type = PLANE;
		_normal = normal;
		_current.SetTensor(CalculateInertiaTensor());
		_current.recalculate();
		_previous = _current;
	}

	Matrix3 CPlane_Object::CalculateInertiaTensor()
	{
		return Matrix3(0.0f);
		//return Matrix3(1.0f);
	}
}