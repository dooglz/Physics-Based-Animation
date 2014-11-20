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
