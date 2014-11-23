#include "Maths.h"
#include "Utilities.h"

#if defined(_PC_)
	#include "glm/glm.hpp"
	#include "glm/gtc/quaternion.hpp"
	#include "glm/gtx/euler_angles.hpp"
	#include "glm/gtc/matrix_transform.hpp"

	void EulerToAngleAxis(const Vector3 euler, Vector3 &axis, float &angle)
	{
		Quaternion q = EulerToQuat(euler);
		axis = glm::axis(q);
		angle = glm::angle(q);
	}

	void QuatToAngleAxis(const Quaternion q, Vector3 &axis, float &angle)
	{
		axis = glm::axis(q);
		angle = glm::angle(q);
	}

	void MatrixToAngleAxis(const Matrix4 m, Vector3 &axis, float &angle){
		Quaternion q = MatrixToQuat(m);
		axis = glm::axis(q);
		angle = glm::angle(q);
	}

	//--
	Vector3 Normalize(Vector3 v)
	{
		v = glm::normalize(v);
		if (isnan(v.x) || isnan(v.y) || isnan(v.z))
		{
			return Vector3(0, 0, 0);
		}
		return v;
	}
	Vector4 Normalize(Vector4 v)
	{
		v = glm::normalize(v);
		if (isnan(v.x) || isnan(v.y) || isnan(v.z))
		{
			return Vector4(0, 0, 0, 0);
		}
		return v;
	}


	Quaternion Normalize(Quaternion q)
	{
		q = glm::normalize(q);
		if (isnan(q.x) || isnan(q.y) || isnan(q.z) || isnan(q.w))
		{
			return Quaternion(0, 0, 0, 0);
		}
		return q;
	}


	Vector3 QuatToEuler(const Quaternion q)
	{
		return glm::eulerAngles(q);
	}

	Vector3 AngleAxisToEuler(const Vector3 axis, const float angle){
		return QuatToEuler(AngleAxisToQuat(axis, angle));
	}
	//only translate

	Vector3 MatrixToEuler(const Matrix4 m){
		return QuatToEuler(MatrixToQuat(m));
	}

	Vector3 GetTransaltion(const Matrix4 m){
		return Vector3(m[3]);
	}


	//--
	Quaternion EulerToQuat(const Vector3 euler){
		return Quaternion(euler);
	}

	Quaternion AngleAxisToQuat(const Vector3 axis, const float angle){
		return glm::angleAxis(angle, axis);
	}

	Quaternion MatrixToQuat(const Matrix4 m){
		return glm::quat_cast(m);
	}

	//--
	Matrix4 EulerToMatrix(const Vector3 euler)
	{
		return  glm::eulerAngleYXZ(euler.y, euler.x, euler.z);
	}

	Matrix4 QuatToMatrix(const Quaternion q)
	{
		return glm::mat4_cast(q);
	}

	Matrix3 QuatToMatrix3(const Quaternion q)
	{
		return glm::mat3_cast(q);
	}

	// Angle in Radians
	Matrix4 AngleAxisToMatrix(const Vector3 axis, const float angle)
	{
		return glm::rotate(glm::mat4(1.0f), angle, axis);
	}

	bool isZero(const Vector3 v3){
		return(abs(v3.x) == 0 && abs(v3.y) == 0 && abs(v3.z) == 0);
	}

	Vector3 cross(const Vector3 a, const Vector3 b)
	{
		return glm::cross(a, b);
	}

	Matrix4 Translation(const Vector3 translationVector)
	{
		return glm::translate(glm::mat4(1.0f), translationVector);
	}

	Matrix4 Scale(const Vector3 scaleVector)
	{
		return glm::scale(glm::mat4(1.0f), scaleVector);
	}

#endif

Vector3 GetForwardVector(Quaternion q)
{
	return Vector3(2.0f * (q.x * q.z + q.w * q.y),
		2.0f * (q.y * q.x - q.w * q.x),
		1.0f - 2.0f * (q.x * q.x + q.y * q.y));
}

Vector3 GetUpVector(Quaternion q)
{
	return Vector3(2 * (q.x * q.y - q.w * q.z),
		1.0f - 2.0f * (q.x * q.x + q.z * q.z),
		2.0f * (q.y * q.z + q.w * q.x));
}

Vector3 GetRightVector(Quaternion q)
{
	return Vector3(1.0f - 2.0f * (q.y * q.y + q.z * q.z),
		2.0f * (q.x * q.y + q.w * q.z),
		2.0f * (q.x * q.z - q.w * q.y));
}

float Clamp(const float a, const float max)
{
	if (a > max){
		return max;
	}
	return a;
}


Plane::Plane(Vector3 &v1, Vector3 &v2, Vector3 &v3) {

	set3Points(v1, v2, v3);
}
Plane::Plane() {}
Plane::~Plane() {}

void Plane::set3Points(Vector3 &v1, Vector3 &v2, Vector3 &v3)
{
	Vector3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = Normalize(aux2 * aux1);

	point = v2;
	d = -Dot(normal,point);
}

void Plane::setNormalAndPoint(Vector3 &normal, Vector3 &point) {

	this->normal = Normalize(normal);
	d = -Dot(this->normal,point);
}

void Plane::setCoefficients(float a, float b, float c, float d) {

	// set the normal vector
	normal = Vector3(a, b, c);
	//compute the lenght of the vector
	float l = normal.length();
	// normalize the vector
	normal = Vector3(a / l, b / l, c / l);
	// and divide d by th length as well
	this->d = d / l;
}

float Plane::distance(Vector3 &p) {
	return (d + Dot(normal,p));
}
