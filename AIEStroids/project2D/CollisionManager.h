#pragma once
#include "PhysicsBody.h"

#include <vector>
#include <forward_list>

struct CollisionEvent
{
	PhysicsBody* other;
	Vector2 collisionNormal;
	float penetration;
};

struct CollisionManifold
{
	CollisionManifold(PhysicsBody* a, PhysicsBody* b) : a(a), b(b) {}

	PhysicsBody* a;
	PhysicsBody* b;
	Vector2 collisionNormal;
	float penetration;
};

class CollisionManager
{
public:
	//should be called every FIXED_TIME_STEP
	void Update();

private:
	void ResolveCollisions();
	static void ResolveCollision(CollisionManifold manifold);
	static bool CheckAABBCollision(AABB& a, AABB& b);

	std::vector<PhysicsBody*> collisionObjects;
	std::vector<CollisionManifold> collisions;
};

