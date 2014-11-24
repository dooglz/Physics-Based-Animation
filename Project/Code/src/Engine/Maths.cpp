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

	Matrix4 Translation(const Vector3 translationVector)
	{
		return glm::translate(glm::mat4(1.0f), translationVector);
	}

	Matrix4 Scale(const Vector3 scaleVector)
	{
		return glm::scale(glm::mat4(1.0f), scaleVector);
	}

	Vector3 V4toV3(Vector4 v){
		return Vector3(v);
	}

#elif defined(_PS3_)

	void EulerToAngleAxis(const Vector3 euler, Vector3 &axis, float &angle)
	{
		Quaternion q = EulerToQuat(euler);
		QuatToAngleAxis(q, axis, angle);
	}

	void QuatToAngleAxis(const Quaternion q, Vector3 &axis, float &angle)
	{
		Quaternion q1 = q;
		if (q1.getW() > 1){ Normalize(q1); }; // if w>1 acos and sqrt will produce errors, this cant happen if quaternion is normalised
		angle = 2 * acos(q1.getW());
		double s = sqrt(1 - q1.getW()*q1.getW()); // assuming quaternion normalised then w is less than 1, so term always positive.
		if (s < 0.001) // test to avoid divide by zero, s is always positive due to sqrt
		{
			// if s close to zero then direction of axis not important
			axis.setX(q1.getX()); // if it is important that axis is normalised then replace with x=1; y=z=0;
			axis.setY(q1.getY());
			axis.setZ(q1.getZ());
		}
		else 
		{
			axis.setX(q1.getX() / s); // normalise axis
			axis.setY(q1.getY() / s);
			axis.setZ(q1.getZ() / s);
		}
	}
	void MatrixToAngleAxis(const Matrix4 m, Vector3 &axis, float &angle){
		Quaternion q = MatrixToQuat(m);
		QuatToAngleAxis(q, axis, angle);
	}

	//--
	Vector3 Normalize(Vector3 v)
	{
		v = Vectormath::Aos::normalize(v);
		if (isnan(v.getX()) || isnan(v.getY()) || isnan(v.getZ()))
		{
			return Vector3(0, 0, 0);
		}
		return v;
	}
	Vector4 Normalize(Vector4 v)
	{
		v = Vectormath::Aos::normalize(v);
		if (isnan(v.getX()) || isnan(v.getY()) || isnan(v.getZ()) || isnan(v.getW()))
		{
			return Vector4(0, 0, 0, 0);
		}
		return v;
	}

	Quaternion Normalize(Quaternion q)
	{
		q = Vectormath::Aos::normalize(q);
		if (isnan(q.getX()) || isnan(q.getY()) || isnan(q.getZ()) || isnan(q.getW()))
		{
			return Quaternion(0, 0, 0, 0);
		}
		return q;
	}


	Vector3 QuatToEuler(const Quaternion q)
	{
		Quaternion q1 = Normalize(q);
		Vector3 v;
		double test = q1.getX()*q1.getY() + q1.getZ()*q1.getW();
		if (test > 0.499) 
		{ // singularity at north pole
			v.setX(2 * atan2(q1.getX(), q1.getW()));
			v.setY(M_PI / 2);
			v.setZ(0);
			return;
		}
		else if (test < -0.499) 
		{ // singularity at south pole
			v.setX(-2 * atan2(q1.getX(), q1.getW()));
			v.setY(-M_PI / 2);
			v.setZ(0);
			return;
		}
		float sqx = q1.getX()*q1.getX();
		float sqy = q1.getY()*q1.getY();
		float sqz = q1.getZ()*q1.getZ();
		v.setX(atan2(2 * q1.getY()*q1.getW() - 2 * q1.getX()*q1.getZ(), 1 - 2 * sqy - 2 * sqz));
		v.setY(asin(2 * test));
		v.setZ(atan2(2 * q1.getX()*q1.getW() - 2 * q1.getY()*q1.getZ(), 1 - 2 * sqx - 2 * sqz));
		return v;
	}

	Vector3 AngleAxisToEuler(const Vector3 axis, const float angle){
		return QuatToEuler(AngleAxisToQuat(axis, angle));
	}
	//only translate

	Vector3 MatrixToEuler(const Matrix4 m){
		return QuatToEuler(MatrixToQuat(m));
	}

	Vector3 GetTransaltion(const Matrix4 m){
		return Vector3(m.getCol3().getXYZ());
	}


	//--
	Quaternion EulerToQuat(const Vector3 euler){
		//TODO: is this right?
		return Quaternion(euler,1.0f);
	}

	Quaternion AngleAxisToQuat(const Vector3 axis, const float angle){
		
		const double s = sin(angle / 2);
		return Quaternion(
			axis.getX() * s, axis.getY() * s, axis.getZ() * s, cos(angle / 2)
		);
	}

	Quaternion MatrixToQuat(const Matrix4 m){
		return Quaternion(m.getUpper3x3());
	}

	//--
	Matrix4 EulerToMatrix(const Vector3 euler)
	{
		//TODO: is this right?
		Matrix4 m = Matrix4::identity();
		return m.rotationZYX(euler);
	}

	Matrix4 QuatToMatrix(const Quaternion q)
	{
		return Matrix4(q,Vector3(0,0,0));
	}

	Matrix3 QuatToMatrix3(const Quaternion q)
	{
		return Matrix3(q);
	}

	// Angle in Radians
	Matrix4 AngleAxisToMatrix(const Vector3 axis, const float angle)
	{
		//TODO: is this right?
		Matrix4 m = Matrix4::identity();
		return m.rotationZYX(axis*angle);
	}

	bool isZero(const Vector3 v3){
		return(abs(v3.getX()) == 0 && abs(v3.getY()) == 0 && abs(v3.getZ) == 0);
	}

	Matrix4 Translation(const Vector3 translationVector)
	{
		return Matrix4::translation(translationVector);
	}

	Matrix4 Scale(const Vector3 scaleVector)
	{
		return Matrix4::scale(scaleVector);
	}

	Vector3 V4toV3(Vector4 v){
		return v.getXYZ();
	}

#endif

Vector3 GetForwardVector(Quaternion q)
{
	return Vector3(2.0f * (q.getX() * q.getZ() + q.getW() * q.getY()),
		2.0f * (q.getY() * q.getX() - q.getW() * q.getX()),
		1.0f - 2.0f * (q.getX() * q.getX() + q.getY() * q.getY()));
}

Vector3 GetUpVector(Quaternion q)
{
	return Vector3(2 * (q.getX() * q.getY() - q.getW() * q.getZ()),
		1.0f - 2.0f * (q.getX() * q.getX() + q.getZ() * q.getZ()),
		2.0f * (q.getY() * q.getZ() + q.getW() * q.getX()));
}

Vector3 GetRightVector(Quaternion q)
{
	return Vector3(1.0f - 2.0f * (q.getY() * q.getY() + q.getZ() * q.getZ()),
		2.0f * (q.getX() * q.getY() + q.getW() * q.getZ()),
		2.0f * (q.getX() * q.getZ() - q.getW() * q.getY()));
}

float Clamp(const float a, const float max)
{
	if (a > max){
		return max;
	}
	return a;
}
