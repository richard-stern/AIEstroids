//
// Author: Matin Kamali
//
#include "Matrix3.h"
#include "Vector2.h"
#include <cmath>
#include <iostream>   // for debugging
//
// create an identity matrix
//

Matrix3::Matrix3() {
	ResetToIdentity();
}

//
// copy
//

Matrix3::Matrix3(const Matrix3& _other) {
	m[0] = _other.m[0];
	m[1] = _other.m[1];
	m[2] = _other.m[2];
	m[3] = _other.m[3];
	m[4] = _other.m[4];
	m[5] = _other.m[5];
	m[6] = _other.m[6];
	m[7] = _other.m[7];
	m[8] = _other.m[8];
}

//
// needed this for old mate matrix3::inverse :)
Matrix3::Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8)
{
	m[0] = m0;
	m[1] = m1;
	m[2] = m2;
	m[3] = m3;
	m[4] = m4;
	m[5] = m5;
	m[6] = m6;
	m[7] = m7;
	m[8] = m8;
}

//
// does nothing for now
//

Matrix3::~Matrix3() {}

//
// Multiply with another matrix
//

Matrix3 Matrix3::operator*(const Matrix3& _other) {
	//Matrix multiplication ;)
	Matrix3 mat = Matrix3();
	mat.m[0] = m[0] * _other.m[0] + m[3] * _other.m[1] + m[6] * _other.m[2];
	mat.m[3] = m[0] * _other.m[3] + m[3] * _other.m[4] + m[6] * _other.m[5];
	mat.m[6] = m[0] * _other.m[6] + m[3] * _other.m[7] + m[6] * _other.m[8];
	mat.m[1] = m[1] * _other.m[0] + m[4] * _other.m[1] + m[7] * _other.m[2];
	mat.m[4] = m[1] * _other.m[3] + m[4] * _other.m[4] + m[7] * _other.m[5];
	mat.m[7] = m[1] * _other.m[6] + m[4] * _other.m[7] + m[7] * _other.m[8];
	mat.m[2] = m[2] * _other.m[0] + m[5] * _other.m[1] + m[8] * _other.m[2];
	mat.m[5] = m[2] * _other.m[3] + m[5] * _other.m[4] + m[8] * _other.m[5];
	mat.m[8] = m[2] * _other.m[6] + m[5] * _other.m[7] + m[8] * _other.m[8];

	return mat;
}

Matrix3 Matrix3::operator=(const Matrix3& _other) {
	m[0] = _other.m[0];
	m[1] = _other.m[1];
	m[2] = _other.m[2];
	m[3] = _other.m[3];
	m[4] = _other.m[4];
	m[5] = _other.m[5];
	m[6] = _other.m[6];
	m[7] = _other.m[7];
	m[8] = _other.m[8];
	return *this;
}

bool Matrix3::operator==(const Matrix3& _other) {
	return m[0] == _other.m[0] && m[1] == _other.m[1] && \
		   m[2] == _other.m[2] && m[3] == _other.m[3] && \
		   m[4] == _other.m[4] && m[5] == _other.m[5] && \
		   m[6] == _other.m[6] && m[7] == _other.m[7] && \
		   m[8] == _other.m[8];
}

Matrix3 Matrix3::operator *(float scalar)
{
	return Matrix3(m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar, m[4] * scalar, m[5] * scalar, m[6] * scalar, m[7] * scalar, m[8] * scalar);
}

void Matrix3::ResetToIdentity() {
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;
	m[6] = 0;
	m[7] = 0;
	m[8] = 1;
}

void Matrix3::SetRotateX(float _radians) {
	// X doesn't change
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = cos(_radians);
	m[5] = sin(_radians);
	m[6] = 0;
	m[7] = -sin(_radians);
	m[8] = cos(_radians);
}

void Matrix3::SetRotateY(float _radians) {
	// Y doesn't change
	m[0] = cos(_radians);
	m[1] = 0;
	m[2] = -sin(_radians);
	m[3] = 0;
	m[4] = 1;
	m[5] = 0;
	m[6] = sin(_radians);
	m[7] = 0;
	m[8] = cos(_radians);
}

void Matrix3::SetRotateZ(float _radians) {
	// Z doesn't change
	m[0] = cos(_radians);
	m[1] = sin(_radians);
	m[3] = -sin(_radians);
	m[4] = cos(_radians);
}

void Matrix3::SetScale(float _x, float _y) {
	Vector2 right = { m[0], m[1] };
	Vector2 up = { m[3], m[4] };

	right = right.GetNormalised() * _x;
	up = up.GetNormalised() * _y;

	m[0] = right.x;
	m[1] = right.y;
	m[3] = up.x;
	m[4] = up.y;
}

void Matrix3::SetPosition(float _x, float _y) {
	m[6] = _x;
	m[7] = _y;
}

void Matrix3::SetPosition(Vector2 _vec2) {
	m[6] = _vec2.x;
	m[7] = _vec2.y;
}

Vector2 Matrix3::GetPosition() const {
	return Vector2(m[6], m[7]);
}

Vector2 Matrix3::GetUp() const {
	Vector2 result(m[3], m[4]);
	result = result.GetNormalised();
	return result;
}

Vector2 Matrix3::GetRight() const {
	Vector2 result(m[0], m[1]);
	result = result.GetNormalised();
	return result;
}

Matrix3 Matrix3::Inverse() const
{
	//Gets matrix of minors, negates every second element, moves each element diagonally to the opposite side
	Matrix3 minors = Matrix3();
	minors.m[0] = (m[4] * m[8] - m[7] * m[5]);	minors.m[3] = (m[1] * m[8] - m[7] * m[2]); minors.m[6] = (m[1] * m[5] - m[4] * m[2]);
	minors.m[1] = (m[3] * m[8] - m[6] * m[5]);	minors.m[4] = (m[0] * m[8] - m[6] * m[2]); minors.m[7] = (m[0] * m[5] - m[3] * m[2]);
	minors.m[2] = (m[3] * m[7] - m[4] * m[6]);	minors.m[5] = (m[0] * m[7] - m[6] * m[1]); minors.m[8] = (m[0] * m[4] - m[3] * m[1]);

	Matrix3 adjugate = Matrix3(minors.m[0], -minors.m[3], minors.m[6], -minors.m[1], minors.m[4], -minors.m[7], minors.m[2], -minors.m[5], minors.m[8]);

	float determinant = (m[0] * minors.m[0]) - (m[3] * minors.m[3]) + (m[6] * minors.m[6]);

	if (determinant == 0)
		throw ("Cannot divide adjugate by 0");

	return adjugate * (1 / determinant);
}

Vector2 Matrix3::GetScale()
{
	return Vector2(Vector2(m[0], m[1]).GetMagnitude(), Vector2(m[3], m[4]).GetMagnitude());
}

float Matrix3::GetRotation()
{
	Vector2 right = GetRight();
	return std::atan2(right.y, right.x);
}

void Matrix3::SetRotation(float radians)
{
	Vector2 scale = GetScale();

	SetRotateZ(radians);

	m[0] *= scale.x;
	m[1] *= scale.x;
	m[3] *= scale.y;
	m[4] *= scale.y;
}

void Matrix3::Print() {
	std::cout << "\nmatrix\n";
	for (int i = 0; i < 9; ++i) {
		std::cout << m[i] << "|";
		if (i == 2 || i == 5)
			std::cout << '\n';
	}
}