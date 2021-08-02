#pragma once
#include "Vector2.h"
#include <memory>

struct AABB
{
	Vector2 topLeft;
	Vector2 bottomRight;
};

enum class ShapeType
{
	CIRCLE,
	POLYGON
};

struct Shape
{
	virtual ShapeType getType() = 0;
	Vector2 centrePoint;
};

struct CircleShape : public Shape
{
	float radius;

	CircleShape(Vector2 centrePoint, float radius)
		: radius(radius)
	{
		this->centrePoint = centrePoint;
	}

	ShapeType getType() { return ShapeType::CIRCLE; }
};

struct PolygonShape : public Shape
{
	Vector2* vertices;
	Vector2* normals;
	int count;

	PolygonShape(Vector2* vertices, Vector2* normals, Vector2 centrePoint, int count)
		: vertices(vertices), normals(normals), count(count)
	{
		this->centrePoint = centrePoint;
	}
	~PolygonShape();

	ShapeType getType() { return ShapeType::POLYGON; }
	void CloneTo(PolygonShape& shape);
};
