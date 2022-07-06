#ifndef _H_QUATERNION_
#define _H_QUATERNION_
#include "Engine.h"

class Quaternion {
public:
	float w, x, y, z;
public:
	Quaternion();
	Quaternion(float W, float X, float Y, float Z);
	Quaternion(const Quaternion& q);
	~Quaternion();
	Quaternion& operator=(const Quaternion&);

	bool operator==(Quaternion& rhs);
	bool operator!=(Quaternion& rhs);

	Quaternion& operator*=(Quaternion& rhs);
	Quaternion& operator*=(const Quaternion& rhs);
	Quaternion operator*(Quaternion& rhs);
	const Quaternion operator*(const Quaternion& rhs);
	Quaternion operator*(float& rhs);
	const Quaternion operator*(const float& rhs);
	Quaternion operator+(Quaternion& rhs);
	const Quaternion operator+(const Quaternion& rhs);
	Vector operator*(Vector& rhs);
	//const Vector operator*(const Vector& rhs);

	Quaternion Normalized();
	void Normalize();
	Quaternion Conjugate(); // Same as inverse

	void ToAngleAxis(float* angle, Vector* axis);
	void SetEuler(float X, float Y, float Z);
	float Dot(Quaternion& b);
	//void SetLookRotation(Vector& lookAt);
	//void SetLookRotation(Vector& lookAt, Vector& upDirection);

	//static Quaternion LookRotation(Vector& lookAt);
	//static Quaternion LookRotation(Vector& lookAt, Vector& upDirection);
	static Quaternion Slerp(Quaternion& from, Quaternion& to, float t);
	static Quaternion Lerp(Quaternion& from, Quaternion& to, float t);
	static float Angle(Quaternion& a, Quaternion& b);
	static float Dot(Quaternion& a, Quaternion& b);
	static Quaternion AngleAxis(float angle, Vector& axis);
	static Quaternion Inverse(Quaternion& rotation);
	static Quaternion Euler(float X, float Y, float Z);
	static Matrix ToMatrix(Quaternion& q);

	static const Quaternion identity;
};

//const Vector operator*(Vector& v, const Quaternion& m);
//Vector operator*(Vector& v, Quaternion& m);
Quaternion operator*(float f, Quaternion& m);
const Quaternion operator*(float f, const Quaternion& m);

#endif