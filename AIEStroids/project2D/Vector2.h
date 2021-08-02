//
// Author: Matin Kamali
//
#ifndef VECTOR_2_H
#define VECTOR_2_H

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
	Vector2 get_perpendicular() const;
	Vector2 get_normalised() const;
	float get_magnitude() const;
	float get_dot(Vector2 other) const;
	float get_angle() const;
	float get_angle_degree() const;
	float get_distance_to(const Vector2& other) const;
	void rotate(float _radians);

	// -------------- //
	// STATIC METHODS //
	// -------------- //
	static float get_angle_between(Vector2 _vec1, Vector2 _vec2);
	static Vector2 ZERO() { return Vector2();}
};

#endif //VECTOR_2_H