#include "Shape.h"

void Shape::CalculateGlobal(Matrix3& transform)
{
	globalCentrePoint = centrePoint * transform;
}

PolygonShape::~PolygonShape()
{
	delete[] vertices;
	delete[] normals;
	delete[] globalVertices;
}

void PolygonShape::CloneTo(PolygonShape& shape)
{
	shape.vertices = new Vector2[count];
	shape.normals = new Vector2[count];
	memcpy(shape.vertices, this->vertices, count * sizeof(Vector2));
	memcpy(shape.normals, this->normals, count * sizeof(Vector2));
	shape.centrePoint = centrePoint;
	shape.count = count;
}

void PolygonShape::CalculateGlobal(Matrix3& transform)
{
	globalCentrePoint = centrePoint * transform;
	
	for (int i = 0; i < count; i++)
	{
		globalVertices[i] = globalVertices[i] * transform;
	}
}
