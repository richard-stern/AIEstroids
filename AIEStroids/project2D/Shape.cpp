#include "Shape.h"



PolygonShape::~PolygonShape()
{
	delete[] vertices;
	delete[] normals;
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
