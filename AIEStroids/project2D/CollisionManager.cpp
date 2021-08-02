#include "CollisionManager.h"

CollisionManager* CollisionManager::instance = nullptr;

void CollisionManager::Update()
{
	for (int i = 0; i < collisionObjects.size(); i++)
	{
		collisionObjects[i]->Update();
	}

	ResolveCollisions();
}

void CollisionManager::CreateInstance()
{
	instance = new CollisionManager();
}

void CollisionManager::DeleteInstance()
{
	delete instance;
	instance = nullptr;
}

CollisionManager* CollisionManager::GetInstance()
{
	return instance;
}

void CollisionManager::ResolveCollisions()
{
	collisions.clear();

	for (int i = 0; i < collisionObjects.size() - 1; i++)
	{
		for (int j = 1; j < collisionObjects.size(); j++)
		{
			//check if the objects can collide or not
			if (collisionObjects[i]->collider->collisionLayer & collisionObjects[j]->collider->collisionMask
				&& collisionObjects[j]->collider->collisionLayer & collisionObjects[i]->collider->collisionMask)
			{
				//broad phase
				//this checks if the AABBs are colliding
				if (CheckAABBCollision(collisionObjects[i]->collider->shapeAABB, collisionObjects[j]->collider->shapeAABB))
				{
					//in this case we need to check if collision is valid, and if so, resolve it
					//we add it to collisions for this frame
					collisions.push_back(CollisionManifold(collisionObjects[i], collisionObjects[j]));
				}
			}
		}
	}

	//now that all possible collisions have been found, resolve collisions
	for (int i = 0; i < collisions.size(); i++)
	{
		ResolveCollision(collisions[i]);
	}
}

void CollisionManager::ResolveCollision(CollisionManifold& manifold)
{

}

bool CollisionManager::CheckAABBCollision(AABB& a, AABB& b)
{
	return (a.bottomRight.x > b.topLeft.x&& a.bottomRight.y > b.topLeft.x
		&& a.topLeft.x < b.bottomRight.x && a.topLeft.y < b.bottomRight.y);
}

bool CollisionManager::getCollisionInfo(CollisionManifold& manifold)
{
	return false;
}
