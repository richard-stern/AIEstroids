#pragma once
#include "Vector2.h"
#include <memory>

struct Shape
{
	Vector2* vertices;
	Vector2* normals;
	Vector2 centrePoint;
	int count;

	Shape(Vector2* vertices, Vector2* normals, Vector2 centrePoint, int count)
		: vertices(vertices), normals(normals), centrePoint(centrePoint), count(count)	{}
	~Shape();

	Shape&& clone();
	
};
