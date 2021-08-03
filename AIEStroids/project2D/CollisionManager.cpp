#include "CollisionManager.h"
#include "Actor.h"

CollisionManager* CollisionManager::instance = nullptr;

void CollisionManager::Update()
{
	ResolveCollisions();

	for (int i = 0; i < collisionObjects.size(); i++)
	{
		collisionObjects[i]->Update(aie::Application::GetInstance()->GetDeltaTime());
	}
}

void CollisionManager::AddBody(PhysicsBody* body)
{
	collisionObjects.push_back(body);
	body->GetCollider()->GetShape()->CalculateGlobal(body->actorObject->GetGlobalTransform());
}

void CollisionManager::CreateInstance()
{
	if (instance != nullptr)
	{
		delete instance;
	}
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
		if (collisionObjects[i]->collider == nullptr)
		{
			continue;
		}

		for (int j = 1; j < collisionObjects.size(); j++)
		{
			if (collisionObjects[i]->collider == nullptr)
			{
				continue;
			}
			//check if the objects are compatible layer wise
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
	//if collision happened
	if (getCollisionInfo(manifold))
	{
		//resolve collision

		Vector2 rV = manifold.b->GetVelocity() - manifold.a->GetVelocity();
		float projectedRV = manifold.collisionNormal.GetDot(rV);
		float impulseMagnitude = -(1 + std::min(manifold.a->collider->restitution, manifold.b->collider->restitution) * projectedRV) / (manifold.a->GetInverseMass() + manifold.b->GetInverseMass());
		Vector2 impulse = manifold.collisionNormal * impulseMagnitude;

		manifold.a->AddImpulse(impulse * -1);
		manifold.b->AddImpulse(impulse);
	}
}

bool CollisionManager::CheckAABBCollision(AABB& a, AABB& b)
{
	return (a.bottomRight.x > b.topLeft.x&& a.bottomRight.y > b.topLeft.x
		&& a.topLeft.x < b.bottomRight.x && a.topLeft.y < b.bottomRight.y);
}

bool CollisionManager::getCollisionInfo(CollisionManifold& manifold)
{
	//for polygon-polygon

	PolygonShape* a = (PolygonShape*)manifold.a->collider->shape;
	auto aVertices = a->GetGlobalVertices();
	auto aNormals = a->GetNormals();
	auto aCount = a->GetCount();
	//get the centre of the shape
	//should be the mean of all points
	Vector2 aCentre = a->GetGlobalCentrePoint();

	PolygonShape* b = (PolygonShape*)manifold.a->collider->shape;
	auto bVertices = b->GetGlobalVertices();
	auto bNormals = ((PolygonShape*)manifold.b->collider->shape)->GetNormals();
	auto bCount = b->GetCount();
	Vector2 bCentre = b->GetGlobalCentrePoint();
	
	//the projection data
	float penetration = INFINITY;
	Vector2 pNormal;

	//loop through a's normals
	for (int i = 0; i < aCount; i++)
	{
		//get minimum and maximum on this axis
		MinMax aResult = GetProjectedMinMax(aNormals[i], aVertices, aCount);
		MinMax bResult = GetProjectedMinMax(aNormals[i], bVertices, bCount);

		//check if colliding (on this axis)
		if ((aResult.min < bResult.max && aResult.min < bResult.min)
			|| (bResult.min < aResult.max && bResult.min > aResult.min))
		{
			//need to get distance between maximum and minimum
			float length = aResult.max > bResult.min ? aResult.max - bResult.min : bResult.max - aResult.min;
			//then get the size of the shapes on the axis
			//pvalue equals total size of both shapes - length between both shapes 
			float pValue = ((aResult.max - aResult.min) + (bResult.max - bResult.min)) - length;

			//if smallest penetration, set it to penetration vector
			if (pValue < penetration)
			{
				penetration = pValue;
				pNormal = bNormals[i];
			}
		}
		//if not they are not colliding, so return
		else 
			return false;
	}

	//loop through b's
	for (int i = 0; i < bCount; i++)
	{
		//get minimum and maximum on this axis
		MinMax aResult = GetProjectedMinMax(bNormals[i], aVertices, aCount);
		MinMax bResult = GetProjectedMinMax(bNormals[i], bVertices, bCount);

		//check if colliding (on this axis)
		if ((aResult.min < bResult.max && aResult.min < bResult.min)
			|| (bResult.min < aResult.max && bResult.min > aResult.min))
		{
			//need to get distance between maximum and minimum
			float length = aResult.max > bResult.min ? aResult.max - bResult.min : bResult.max - aResult.min;
			//then get the size of the shapes on the axis
			//pvalue equals total size of both shapes - length between both shapes 
			float pValue = ((aResult.max - aResult.min) + (bResult.max - bResult.min)) - length;
			
			//if smallest penetration, set it to penetration vector
			if (pValue < penetration)
			{
				penetration = pValue;
				pNormal = bNormals[i];
			}
		}
		//if not they are not colliding, so return
		else
			return false;
	}

	//if reached this point without exiting, they are colliding.
	//set penetration data in manifold
	manifold.penetration = penetration;
	manifold.collisionNormal = pNormal;
}

MinMax CollisionManager::GetProjectedMinMax(Vector2& axis, Vector2* vertices, int vertexCount)
{
	MinMax results;
	results.min = INFINITY;
	results.max = -INFINITY;

	//loop through all vertices
	for (int i = 0; i < vertexCount; i++)
	{
		float projectedValue = axis.GetDot(vertices[i]);

		//if this is the minimum value, set it to min
		if (projectedValue < results.min)
			results.min = projectedValue;

		//if this is the maximum value, set it to max
		if (projectedValue > results.max)
			results.max = projectedValue;
	}

	return results;
}
