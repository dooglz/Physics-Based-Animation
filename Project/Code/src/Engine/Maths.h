#pragma once
#include "Utilities.h"

struct stVertex
{
	float x, y, z;
	unsigned int rgba;
};

#if defined(_PC_)
	#define _USE_MATH_DEFINES
	#define GLM_FORCE_RADIANS
	#include <cmath>
	#include "glm/glm.hpp"
	#include "glm/gtc/quaternion.hpp"
	#include "glm/gtc/matrix_transform.hpp"
	#include "glm/gtc/matrix_inverse.hpp"
	//TODO implement generic methods to change values in vectors
	#define Matrix4 glm::mat4
	#define Matrix3 glm::mat3
	#define Vector4 glm::vec4
	#define Vector3 glm::vec3
	#define Vector2 glm::vec2
	#define Quaternion glm::quat
	#define Length glm::length
	#define Distance glm::distance

	#define Dot glm::dot
	#define Cross glm::cross
	#define Perspective glm::perspective
	#define Inverse glm::inverse
	#define Lookat glm::lookAt
	#ifndef M_PI
		#define M_PI 3.14159265358979323846
	#endif

	//HAX
	#define getX() x
	#define getY() y
	#define getZ() z
	#define setX(a) x=a;
	#define setY(a) y=a;
	#define setZ(a) z=a;
#endif

	void EulerToAngleAxis(const Vector3 euler, Vector3 &axis, float &angle);
	void QuatToAngleAxis(const Quaternion q, Vector3 &axis, float &angle);
	void MatrixToAngleAxis(const Matrix4 m, Vector3 &axis, float &angle);

	Vector3 QuatToEuler(const Quaternion q);
	Vector3 AngleAxisToEuler(const Vector3 axis, const float angle);
	Vector3 MatrixToEuler(const Matrix4 m);
	Vector3 GetTransaltion(const Matrix4 m);

	Quaternion EulerToQuat(const Vector3 euler);
	Quaternion AngleAxisToQuat(const Vector3 axis, const float angle);
	Quaternion MatrixToQuat(const Matrix4 m);

	Matrix4 EulerToMatrix(const Vector3 euler);
	Matrix4 QuatToMatrix(const Quaternion q);
	Matrix4 AngleAxisToMatrix(const Vector3 axis, const float angle);

	Matrix4 Translation(const Vector3 translationVector);
	Matrix4 Scale(const Vector3 scaleVector);

	Vector3 Normalize(Vector3 v);
	Vector4 Normalize(Vector4 v);
	Quaternion Normalize(Quaternion q);

	Vector3 GetForwardVector(Quaternion q);
	Vector3 GetUpVector(Quaternion q);
	Vector3 GetRightVector(Quaternion q);
	
	float Clamp(const float a, const float max);


inline int randomColor()
{
	int x = rand() & 0xff;
	x |= (rand() & 0xff) << 8;
	x |= (rand() & 0xff) << 16;
	x |= (rand() & 0xff) << 24;

	return x;
}