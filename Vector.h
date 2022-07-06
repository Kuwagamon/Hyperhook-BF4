#pragma once
class Vector
{
public:
	float x, y, z;

	Vector();
	Vector(float _x, float _y, float _z);
	Vector(float xyz);
	Vector(float* xyz);

	constexpr bool operator==(const Vector& other) const;
	constexpr bool operator!=(const Vector& other) const;

	constexpr Vector operator+(const Vector& other) const;
	constexpr Vector operator-(const Vector& other) const;
	constexpr Vector operator*(const Vector& other) const;
	constexpr Vector operator/(const Vector& other) const;

	constexpr Vector& operator+=(const Vector& other);
	constexpr Vector& operator-=(const Vector& other);
	constexpr Vector& operator*=(const Vector& other);
	constexpr Vector& operator/=(const Vector& other);

	constexpr float Length() const;
	constexpr float Dot() const;
	constexpr float Dor(const Vector& other) const;
};

class Vector2D
{
public:
	float x, y;

	Vector2D(float _x, float _y);
	Vector2D(float xy);
	Vector2D(float* xy);
};