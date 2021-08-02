//Author: Connor

#pragma once
#include "Vector2.h"
#include "Matrix3.h"
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
	virtual ShapeType GetType() = 0;
	Vector2 centrePoint;

	virtual void CalculateGlobal(Matrix3& transform);
	Vector2 getGlobalCentrePoint() { return globalCentrePoint; }
protected:
	Vector2 globalCentrePoint;
};

struct CircleShape : public Shape
{
	float radius;

	CircleShape(Vector2 centrePoint, float radius)
		: radius(radius)
	{
		this->centrePoint = centrePoint;
	}

	ShapeType GetType() { return ShapeType::CIRCLE; }
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
		globalVertices = new Vector2[count];
	}
	~PolygonShape();

	ShapeType GetType() { return ShapeType::POLYGON; }
	void CloneTo(PolygonShape& shape);

	void CalculateGlobal(Matrix3& transform) override;

	Vector2* GetGlobalVertices() { return globalVertices; };

private:
	//store these just because it is faster probably
	Vector2* globalVertices;
};
