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

Vector2 Vector2::get_perpendicular() const {
	return Vector2(-y, x);
}

Vector2 Vector2::get_normalised() const {
	Vector2 result(x, y);
	float magnitude = result.get_magnitude();

	if (magnitude != 0) {
		result.x /= magnitude;
		result.y /= magnitude;
	}

	return result;
}

float Vector2::get_magnitude() const {
	return sqrtf(x * x + y * y);
}

float Vector2::get_dot(Vector2 other) const {
	return x * other.x + y * other.y;
}

float Vector2::get_angle() const {
	return atan2(x, y);
}

float Vector2::get_angle_degree() const {
	return get_angle() * 180 / (float)M_PI;
}

void Vector2::rotate(float _radians) {
	x = cosf(_radians);
	y = sinf(_radians);
}

float Vector2::get_angle_between(Vector2 _vec1, Vector2 _vec2) {
	// get the dot product of the two vectors
	_vec1 = _vec1.get_normalised();
	_vec2 = _vec2.get_normalised();
	float dot = _vec1.get_dot(_vec2);

	// get angle
	float angle = acosf(dot);

	// get the dot product of one of the vectors and another vector at right angles
	Vector2 perp_vec = _vec1.get_perpendicular();
	float perp_dot = _vec2.get_dot(perp_vec);   // <!> double check if this should be _vec1.get_dot(...)

	if (perp_dot < 0) {
		angle = angle * -1.0f;
	}

	return angle;
}

float Vector2::get_distance_to(const Vector2& other) const {
	return (other - *this).get_magnitude();
}