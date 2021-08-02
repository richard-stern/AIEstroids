#include "CollisionManager.h"

void CollisionManager::Update()
{
	for (int i = 0; i < collisionObjects.size(); i++)
	{
		collisionObjects[i]->Update();
	}

	ResolveCollisions();
}

void CollisionManager::ResolveCollisions()
{
	collisions.clear();

	for (int i = 0; i < collisionObjects.size() - 1; i++)
	{
		

		for (int j = 1; j < collisionObjects.size(); j++)
		{

			//broad phase
			/*if (CheckAABBCollision(collisionObjects[j]->getAABB(), collisionObjects[j]->getAABB()))
			{
			
			}*/
		}
	}
}

void CollisionManager::ResolveCollision(CollisionManifold manifold)
{
}

bool CollisionManager::CheckAABBCollision(AABB& a, AABB& b)
{
	return false;
}
