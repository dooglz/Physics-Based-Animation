#pragma once
class Vector3
{
public:
	float x, y, z;

	Vector3(float x, float y, float z);
	Vector3();

	void operator+= (const Vector3 &v);
	Vector3 operator/  (const float &v) const;
	Vector3 operator-  (const Vector3 &v) const;
	Vector3 operator+  (const Vector3 &v) const;
	Vector3 operator*  (const float &v) const;
	Vector3 operator-  () const;

	static Vector3 Cross(const Vector3 &vA, const Vector3& vB);
	static float Dot(const Vector3 &vA, const Vector3& vB);
	static Vector3 Normalize(const Vector3& v);
	float Length() const;
	float LengthSq() const;

};

class Matrix4
{
public:
	float m[16];
	Matrix4();
	Matrix4(float _00, float _10, float _20, float _30,
		float _01, float _11, float _21, float _31,
		float _02, float _12, float _22, float _32,
		float _03, float _13, float _23, float _33);

	float&	operator[]	(int index);
	const float&	operator[]	(int index) const;

	static Matrix4 Zero();
	static Matrix4 Identity();
	static Matrix4 SetTranslation(const Vector3& translation);
	Vector3 GetTranslation() const;
	static Matrix4 SetRotationAxis(const Vector3& axis, const float angle);
	static Vector3 Transform(const Matrix4& mat, const Vector3& p);
	static Matrix4 Transpose(const Matrix4& mat);
};

//Not actually a member of the M4 class.
Matrix4 operator* (const Matrix4& rhs, const Matrix4& lhs);

//---------------------------- Quaternion
class Quaternion
{
public:
	float x, y, z, w;

	Quaternion(float x, float y , float z, float w);
	Quaternion(const Quaternion& rhs);

	Quaternion& operator= (const Quaternion& rhs);

	Quaternion& operator*= (const Quaternion& rhs);
	Quaternion& operator+= (const Quaternion& rhs);

	// convenience function for the identity quaternion
	static Quaternion Identity();
	static Quaternion Conjugate(const Quaternion& q);

	static float Length(const Quaternion& q);
	static float LengthSq(const Quaternion& q);

	static Quaternion Normalize(const Quaternion& q);

	static float Dot(const Quaternion& q1, const Quaternion& q2);

	static Quaternion FromAxisAngle(const Vector3& v, float angle);

	static float ToAxisAngle(const Quaternion& q, Vector3& v);

	static Matrix4 ToRotationMatrix(const Quaternion& q);

	static Quaternion FromRotationMatrix(const Matrix4& m);

	static Quaternion Slerp(float t, const Quaternion& p, const Quaternion& q);

};


inline
Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y,
		q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z,
		q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x,
		q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z);
}

inline
Quaternion operator+(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(q1.x + q2.x,
		q1.y + q2.y,
		q1.z + q2.z,
		q1.w + q2.w);
}


// Some wrapper functions - ...

Matrix4 SetTranslation(const Vector3& p);

Vector3 GetTranslation(const Matrix4& m);
float Sign(float f);

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

Quaternion Normalize(const Quaternion& q);

Vector3 Cross(const Vector3& v0, const Vector3& v1);

Quaternion Conjugate(const Quaternion& q);

float Dot(const Vector3& v0, const Vector3& v1);

Matrix4 ToRotationMatrix(const Quaternion& q);

Matrix4 SetRotationAxis(const Vector3& axis, float angle);

Quaternion FromAxisAngle(const Vector3& axis, float angle);

float ToAxisAngle(const Quaternion& q, Vector3& axis);

Vector3 Normalize(const Vector3& v);

float Length(const Vector3& v);

Vector3 Transform(const Matrix4& m, const Vector3& v);