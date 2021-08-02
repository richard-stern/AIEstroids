// Author: Matin Kamali

#ifndef RECT_H
#define RECT_H

#include "Vector2.h"

struct Rect {
		Vector2 origin;
		Vector2 size;
		
		Rect();
		Rect(float x, float y, float w, float h);
		Rect(Vector2 _origin, Vector2 _size);

		// methods
		bool is_point_inside(float x, float y) const;

		// operators
		Rect operator+(const Rect& _other);
		Rect operator-(const Rect& _other);
		void operator+=(const Rect& _other);
		void operator-=(const Rect& _other);
		Rect operator*(const Rect& _other) const;
		Rect operator*(float _value) const;
		bool operator==(const Rect& _other) const;
		bool operator!=(const Rect& _other) const;
	};

#endif// RECT_H