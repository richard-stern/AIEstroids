#include "Shape.h"

Shape::~Shape()
{
	delete[] vertices;
	delete[] normals;
}

Shape&& Shape::clone()
{
	auto vertices = new Vector2[count];
	auto normals = new Vector2[count];
	memcpy(vertices, this->vertices, count * sizeof(Vector2));
	memcpy(normals, this->normals, count * sizeof(Vector2));

	return Shape(vertices, normals, centrePoint, count);
}
