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

enum class ShapeType : char
{
	CIRCLE,
	POLYGON
};

class Shape
{
public:
	virtual ShapeType GetType() = 0;

	virtual void CalculateGlobal(Matrix3& transform);
	Vector2 GetGlobalCentrePoint() { return globalCentrePoint; }
	void SetCentrePoint(Vector2 centrePoint) { this->centrePoint = centrePoint; }
	Vector2 GetCentrePoint() { return centrePoint; }

protected:
	Vector2 centrePoint;
	Vector2 globalCentrePoint;
};

class CircleShape : public Shape
{
public:
	CircleShape(Vector2 centrePoint, float radius)
		: radius(radius)
	{
		this->centrePoint = centrePoint;
	}

	ShapeType GetType() { return ShapeType::CIRCLE; }
	float GetRadius() { return radius; }
	int SetRadius(float rad) { radius = rad; }

private:
	float radius;
};

class PolygonShape : public Shape
{
public:
	//vertices should be stored clockwise
	PolygonShape(Vector2* vertices, Vector2 centrePoint, int count)
		: vertices(vertices), count(count)
	{
		this->centrePoint = centrePoint;
		GenerateNormals();
		globalVertices = new Vector2[count];
	}
	~PolygonShape();

	ShapeType GetType() { return ShapeType::POLYGON; }
	void CloneTo(PolygonShape& shape);

	void CalculateGlobal(Matrix3& transform) override;

	Vector2* GetGlobalVertices() { return globalVertices; };
	Vector2* GetVertices() { return vertices; };
	Vector2* GetNormals() { return normals; };
	int GetCount() { return count; };

	//reletive centrepoint is relative to the global position of the actor
	static PolygonShape* CreateBox(float hx, float hy, Vector2 relativeCentrePoint);
	static PolygonShape* CreatePoly(float vertexCount, float radius, Vector2 relativeCentrePoint);

private:
	void GenerateNormals();
	//store global just because it is faster probably
	Vector2* globalVertices = nullptr;
	Vector2* vertices = nullptr;
	Vector2* normals = nullptr;
	int count;
};
