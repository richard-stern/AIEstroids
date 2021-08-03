#include "Collider.h"
#include "PhysicsBody.h"
#include "CollisionManager.h"

Collider::Collider(Shape* shape, unsigned short collisionLayer, unsigned short collisionMask, float density, float restitution, bool isTrigger)
	: shape(shape), collisionLayer(collisionLayer), collisionMask(collisionMask), density(density), restitution(restitution), isTrigger(isTrigger)
{}

float Collider::CalculateMass()
{
	return 1.0f;
}

Collider::~Collider()
{
	if (shape != nullptr)
	{
		delete shape;
	}
}
