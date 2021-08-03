//
// Author: Matin Kamali
//
#ifndef VECTOR_2_H
#define VECTOR_2_H
#define M_PI 3.14159265358979323846
#define DEG2RAD 0.01745329
#define RAD2DEG	57.2957795
#include "Matrix3.h"

#define M_PI 3.14159265358979323846
struct Vector2 {

	// ------ //
	// FIELDS //
	// ------ //
	float x = 0;
	float y = 0;

	// ------------ //
	// CONSTRUCTORS //
	// ------------ //
	Vector2();
	Vector2(float _x, float _y);

	// --------- //
	// OPERATORS //
	// --------- //
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const Vector2& other) const;
	Vector2 operator*(float _value) const;
	Vector2 operator*(const Matrix3& mat) const;
	Vector2 operator/(const Vector2& other) const;
	Vector2 operator/(float _value) const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);
	void operator*=(const Vector2& other);
	void operator*=(float _value);
	void operator/=(const Vector2& other);
	void operator/=(float _value);
	
	// ------- //
	// METHODS //
	// ------- //
	Vector2 GetPerpendicular() const;
	Vector2 GetNormalised() const;
	float GetMagnitude() const;
	float GetDot(Vector2 other) const;
	float GetAngle() const;
	float GetAngleDegrees() const;
	float GetDistance(const Vector2& other) const;
	void SetRotation(float _radians);

	// -------------- //
	// STATIC METHODS //
	// -------------- //
	static float Dot(Vector2 _vec1, Vector2 _vec2);
	static Vector2 Scale(Vector2 _vec1, Vector2 vec2);
	static float GetAngle(Vector2 _vec1, Vector2 _vec2);
	static Vector2 ZERO() { return Vector2(); }
	static Vector2 ONE() { return Vector2(1, 1); }
	static Vector2 UP() { return Vector2(0, 1); }
	static Vector2 RIGHT() { return Vector2(1, 0); }

};

#endif //VECTOR_2_H