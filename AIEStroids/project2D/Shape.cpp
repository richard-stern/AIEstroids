#include "Shape.h"
#include <algorithm> // nocheckin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		SHAPE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Shape::CalculateGlobal(Matrix3& transform)
{
	globalCentrePoint = centrePoint * transform;
	globalCentrePoint += transform.GetPosition();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//		POLYGON SHAPE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
	globalCentrePoint += transform.GetPosition();

	for (int i = 0; i < count; i++)
	{
		globalVertices[i] = vertices[i] * transform;
		globalVertices[i] += globalCentrePoint;
	}
}

float PolygonShape::GetArea()
{
	//this only returns accurate area if centrepoint is inside the shape
	float area = 0;
	for (int i = 0; i < count; i++)
	{
		Vector2 baseVector = vertices[(i + 1) % count] - vertices[i];
		//height should be perpendicular to bade
		float height = abs(Vector2::Dot(baseVector.GetPerpendicular().GetNormalised(), vertices[i] - centrePoint));
		float base = baseVector.GetMagnitude();
		//triangle area
		area += base * height * 0.5f;
	}
	return area;
}

PolygonShape* PolygonShape::CreateBox(float hx, float hy, Vector2 relativeCentrePoint)
{
	Vector2* vertices = new Vector2[4];
	vertices[0] = Vector2(hx, hy);
	vertices[1] = Vector2(hx, -hy);
	vertices[2] = Vector2(-hx, -hy);
	vertices[3] = Vector2(-hx, hy);

	PolygonShape* polygonShape = new PolygonShape(vertices, relativeCentrePoint, 4);
	polygonShape->GenerateNormals();
	return polygonShape;
}

PolygonShape* PolygonShape::CreatePoly(float vertexCount, float radius, Vector2 relativeCentrePoint)
{
	Vector2* vertices = new Vector2[vertexCount];
	float rotationPerPoint = (float)M_PI * 2 / vertexCount;

	for (int i = 0; i < vertexCount; i++)
	{
		Vector2 radiusVector = Vector2::RIGHT() * radius;
		radiusVector.SetRotation((float)M_PI * 2 - rotationPerPoint * i);
		vertices[i] = radiusVector;
	}

	PolygonShape* polygonShape = new PolygonShape(vertices, relativeCentrePoint, 4);
	polygonShape->GenerateNormals();
	return polygonShape;
}

void PolygonShape::GenerateNormals()
{
	if (vertices != nullptr)
	{
		normals = new Vector2[count];

		for (int i = 0; i < count - 1; i++)
		{
			normals[i] = (vertices[i] - vertices[i + 1]).GetNormalised().GetPerpendicular();
		}
		normals[count -1] = (vertices[count - 1] - vertices[0]).GetNormalised().GetPerpendicular();
	}
	
}

void CircleShape::CalculateGlobal(Matrix3& transform)
{
	globalCentrePoint = centrePoint * transform;
	globalCentrePoint += transform.GetPosition();
	auto scale = transform.GetScale();
	globalRadius = radius * std::max(scale.x, scale.y);
}

float CircleShape::GetArea()
{
	return M_PI * radius * radius;
}
