// Author: Matin Kamali

#include "Rect.h"
// ---- //
// RECT //
// ---- //
Rect::Rect() {}

Rect::Rect(Vector2 _origin, Vector2 _size) {
	origin = _origin;
	size   = _size;
}

Rect::Rect(float x, float y, float w, float h) {
	origin.x = x;
	origin.y = y;
	size.x = w;
	size.y = h;
}

Rect Rect::operator+(const Rect& _other) {
	return Rect(origin + _other.origin, size + _other.size);
}

Rect Rect::operator-(const Rect& _other) {
	return Rect(origin - _other.origin, size - _other.size);
}

void Rect::operator+=(const Rect& _other) {
	origin += _other.origin;
	size   += _other.size;
}

void Rect::operator-=(const Rect& _other) {
	origin -= _other.origin;
	size   -= _other.size;
}

Rect Rect::operator*(const Rect& _other) const {
	return Rect(origin * _other.origin, size * _other.size);
}

Rect Rect::operator*(float _value) const {
	return Rect(origin * _value, size * _value);
}

bool Rect::operator==(const Rect& _other) const {
	return origin == _other.origin && size == _other.size;
}

bool Rect::operator!=(const Rect& _other) const {
	return origin != _other.origin || size != _other.size;
}

bool Rect::is_point_inside(float x, float y) const {
	return ((x >= origin.x && x <= origin.x + size.x) && (y >= origin.y && y <= origin.y + size.y));
}