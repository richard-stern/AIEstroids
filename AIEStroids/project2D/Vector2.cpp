//
// Author: Matin Kamali
//
#include "Vector2.h"
#include <math.h>

// ------- //
// Vector2 //
// ------- //

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2 Vector2::operator+(const Vector2& other) const {
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
	return Vector2(x - other.x, y - other.y);
}

void Vector2::operator+=(const Vector2& other) {
	x += other.x;
	y += other.y;
}

void Vector2::operator-=(const Vector2& other) {
	x -= other.x;
	y -= other.y;
}

Vector2 Vector2::operator*(const Vector2& other) const {
	return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator*(float _value) const {
	return Vector2(x * _value, y * _value);
}

void Vector2::operator*=(const Vector2& other) {
	x *= other.x;
	y *= other.y;
}

void Vector2::operator*=(float _value) {
	x *= _value;
	y *= _value;
}

Vector2 Vector2::operator/(const Vector2& other) const {
	Vector2 result;
	result.x = x / other.x;
	result.y = y / other.y;
	return result;
}

Vector2 Vector2::operator/(float _value) const {
	Vector2 result;
	result.x = x / _value;
	result.y = y / _value;
	return result;
}

void Vector2::operator/=(const Vector2& other) {
	x /= other.x;
	y /= other.y;
}

void Vector2::operator/=(float _value) {
	x /= _value;
	y /= _value;
}

bool Vector2::operator==(const Vector2& other) const {
	return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
	return !(*this == other);
}

Vector2 Vector2::GetPerpendicular() const {
	return Vector2(-y, x);
}

Vector2 Vector2::GetNormalised() const {
	Vector2 result(x, y);
	float magnitude = result.GetMagnitude();

	if (magnitude != 0) {
		result /= magnitude;
	}

	return result;
}

float Vector2::GetMagnitude() const {
	return sqrtf(x * x + y * y);
}

float Vector2::GetDot(Vector2 other) const {
	return x * other.x + y * other.y;
}

float Vector2::GetAngle() const {
	return atan2(x, y);
}

float Vector2::GetAngleDegrees() const {
	return GetAngle() * 180 / (float)M_PI;
}

void Vector2::SetRotation(float _radians) {
	float magnitude = GetMagnitude();
	x = cosf(_radians);
	y = sinf(_radians);
	*this *= magnitude;
}

Vector2 Vector2::Scale(Vector2 _vec1, Vector2 _vec2)
{
	return Vector2(_vec1.x * _vec2.x, _vec1.y * _vec2.y);
}

float Vector2::GetAngle(Vector2 _vec1, Vector2 _vec2) {
	// get the dot product of the two vectors
	_vec1 = _vec1.GetNormalised();
	_vec2 = _vec2.GetNormalised();
	float dot = _vec1.GetDot(_vec2);

	// get angle
	float angle = acosf(dot);

	// get the dot product of one of the vectors and another vector at right angles
	Vector2 perp_vec = _vec1.GetPerpendicular();
	float perp_dot = _vec2.GetDot(perp_vec);   // <!> double check if this should be _vec1.get_dot(...)

	if (perp_dot < 0) {
		angle = angle * -1.0f;
	}

	return angle;
}

float Vector2::GetDistance(const Vector2& other) const {
	return (other - *this).GetMagnitude();
}