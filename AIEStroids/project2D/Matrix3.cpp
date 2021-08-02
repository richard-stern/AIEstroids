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
// does nothing for now
//

Matrix3::~Matrix3() {}

//
// Multiply with another matrix
//

Matrix3 Matrix3::operator*(const Matrix3& _other) {
	m[0] = m[0] * _other.m[0] + m[3] * _other.m[1] + m[6] * _other.m[2];
	m[1] = m[1] * _other.m[0] + m[4] * _other.m[1] + m[7] * _other.m[2];
	m[2] = m[2] * _other.m[0] + m[5] * _other.m[1] + m[8] * _other.m[2];
	
	m[3] = m[0] * _other.m[3] + m[3] * _other.m[4] + m[6] * _other.m[5];
	m[4] = m[1] * _other.m[3] + m[4] * _other.m[4] + m[7] * _other.m[5];
	m[5] = m[2] * _other.m[3] + m[5] * _other.m[4] + m[8] * _other.m[5];
	
	m[6] = m[0] * _other.m[6] + m[3] * _other.m[7] + m[6] * _other.m[8];
	m[7] = m[1] * _other.m[6] + m[4] * _other.m[7] + m[7] * _other.m[8];
	m[8] = m[2] * _other.m[6] + m[5] * _other.m[7] + m[8] * _other.m[8];

	return *this;
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
	m[2] = 0;
	m[3] = -sin(_radians);
	m[4] = cos(_radians);
	m[5] = 0;
	m[6] = 0;
	m[7] = 0;
	m[8] = 1;
}

void Matrix3::SetScale(float _x, float _y) {
	Matrix3 scale_matrix;
	scale_matrix.m[0] = _x;
	scale_matrix.m[1] = _y;
	*this = *this * scale_matrix;
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
	result = result.get_normalised();
	return result;
}

Vector2 Matrix3::GetRight() const {
	Vector2 result(m[0], m[1]);
	result = result.get_normalised();
	return result;
}

void Matrix3::Print() {
	std::cout << "\nmatrix\n";
	for (int i = 0; i < 9; ++i) {
		std::cout << m[i] << "|";
		if (i == 2 || i == 5)
			std::cout << '\n';
	}
}