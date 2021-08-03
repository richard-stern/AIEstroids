#include "Collider.h"
#include "PhysicsBody.h"
#include "CollisionManager.h"

Collider::Collider(Shape* shape, unsigned short collisionLayer, unsigned short collisionMask, float density, float restitution)
	: shape(shape), collisionLayer(collisionLayer), collisionMask(collisionMask), density(density), restitution(restitution)
{}

float Collider::CalculateMass()
{
	return shape->GetArea() * density;
}

Collider::~Collider()
{
	if (shape != nullptr)
	{
		delete shape;
	}
}
