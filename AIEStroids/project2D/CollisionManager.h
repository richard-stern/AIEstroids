#pragma once
#include "PhysicsBody.h"

#include <vector>
#include <forward_list>

struct CollisionManifold
{
	Collider* a;
	Collider* b;
	Vector2 collisionNormal;
	float penetration;
};

class CollisionManager
{
public:
	//should be called every FIXED_TIME_STEP
	void Update();

private:
	std::vector<PhysicsBody*> collisionObjects;
	std::vector<CollisionManifold> potentialCollisions;

	
};

