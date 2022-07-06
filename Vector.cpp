#include "Vector.h"

Vector::Vector()
{
    x = y = z = 0.0f;
}

Vector::Vector(float _x, float _y, float _z)
{
    x = _x; y = _y; z = _z;
}

Vector::Vector(float xyz)
{
    x = xyz; y = xyz; z = xyz;
}

Vector::Vector(float* xyz)
{
    x = xyz[0]; y = xyz[1]; z = xyz[2];
}

constexpr bool Vector::operator==(const Vector& other) const
{

    return (x == other.x && y == other.y && z == other.z);
}

constexpr bool Vector::operator!=(const Vector& other) const
{
    return (x != other.x && y != other.y && z != other.z);
}

constexpr Vector Vector::operator+(const Vector& other) const
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

constexpr Vector Vector::operator-(const Vector& other) const
{
    return Vector(x - other.x, y - other.y, z - other.z);
}

constexpr Vector Vector::operator*(const Vector& other) const
{
    return Vector(x * other.x, y * other.y, z * other.z);
}

constexpr Vector Vector::operator/(const Vector& other) const
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

constexpr Vector& Vector::operator+=(const Vector& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}

constexpr Vector& Vector::operator-=(const Vector& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}

constexpr Vector& Vector::operator*=(const Vector& other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    return *this;
}

constexpr Vector& Vector::operator/=(const Vector& other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    return *this;
}

constexpr float Vector::Length() const
{
    return 0.0f;
}

constexpr float Vector::Dot() const
{
    return 0.0f;
}

constexpr float Vector::Dor(const Vector& other) const
{
    return 0.0f;
}

Vector2D::Vector2D(float _x, float _y)
{
}

Vector2D::Vector2D(float xy)
{
}

Vector2D::Vector2D(float* xy)
{
}
