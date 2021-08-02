//
// Author: Matin Kamali
//
#ifndef MATRIX_3_H
#define MATRIX_3_H

struct Vector2;

struct Matrix3 {
	// ------ //
	// fields //
	// ------ //
	float m[9];
	
	// ------------ //
	// constructors //
	// ------------ //
	Matrix3();
	Matrix3(const Matrix3& _other);
	~Matrix3();

	// --------- //
	// operators //
	// --------- //
	Matrix3 operator*(const Matrix3& _other);
	Matrix3 operator=(const Matrix3& _other);
	bool operator==(const Matrix3& _other);

	// ------- //
	// methods //
	// ------- //
	void ResetToIdentity();
	void SetRotateX(float _radians);
	void SetRotateY(float _radians);
	void SetRotateZ(float _radians);
	void SetScale(float _x, float _y);
	void SetPosition(float _x, float _y);
	void SetPosition(Vector2 _vec2);
	Matrix3 Multiply(const Matrix3& _other);
	Vector2 GetPosition() const;
	Vector2 GetUp() const;
	Vector2 GetRight() const;

	// --------- //
	// debugging //
	// --------- //
	void Print();
};

#endif // MATRIX_3_H