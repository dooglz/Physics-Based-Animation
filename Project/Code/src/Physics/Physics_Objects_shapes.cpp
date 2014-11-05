#include "Physics_Objects_shapes.h"

namespace Physics{

	Matrix3 CCube_Object::CalculateInertiaTensor()
	{
		Matrix3 mat;
		mat[0][0] = (_current.mass / 12.0f)*((_size.x*_size.x) + (_size.y*_size.y));
		mat[1][1] = (_current.mass / 12.0f)*((_size.z*_size.z) + (_size.y*_size.y));
		mat[2][2] = (_current.mass / 12.0f)*((_size.z*_size.z) + (_size.x*_size.x));
		return mat;
	}

	CCube_Object::CCube_Object(float mass, Vector3 position, float lw, float lh, float ld) :CPhysicsObject(mass, position)
	{
		_size = Vector3(lw, lh, ld);
		_current.inertiaTensor = CalculateInertiaTensor();
		_current.inverseInertiaTensor = Inverse(_current.inertiaTensor);
		_current.recalculate();
		_previous = _current;
	}

	Matrix3 CSphere_Object::CalculateInertiaTensor()
	{
		return Matrix3(_current.mass * _radius* _radius * (2.0f / 5.0f));

	}

	CSphere_Object::CSphere_Object(float mass, Vector3 position, float radius) :CPhysicsObject(mass, position)
	{
		_radius = radius;
		_current.inertiaTensor = CalculateInertiaTensor();
		_current.inverseInertiaTensor = Inverse(_current.inertiaTensor);
		_current.recalculate();
		_previous = _current;
	}
}