//Author: Connor

#pragma once
#include "Vector2.h"
#include "Shape.h"
class PhysicsBody;
class CollisionManager;

class Collider
{
public:
	Collider(Shape* shape, unsigned short collisionLayer, unsigned short collisionMask, float density = 1, float restitution = 0, bool isTrigger = false);
	float CalculateMass();
	
	~Collider();
private:
	friend PhysicsBody;
	friend CollisionManager;

	Shape* shape;
	AABB shapeAABB;
	unsigned short collisionLayer;
	unsigned short collisionMask;
	float restitution;
	bool isTrigger;
	float density;
};

