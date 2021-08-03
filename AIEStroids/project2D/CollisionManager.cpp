#include "CollisionManager.h"
#include "Actor.h"
#include <iostream>

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
	if (body->GetCollider() != nullptr)
		body->GetCollider()->GetShape()->CalculateGlobal(body->actorObject->GetGlobalTransform());
}

void CollisionManager::RemoveBody(PhysicsBody* body)
{
	auto it = std::find(collisionObjects.begin(), collisionObjects.end(), body);
	if (it != collisionObjects.end())
		collisionObjects.erase(std::find(collisionObjects.begin(), collisionObjects.end(), body));
}

static Vector2 penetrationVector;
static Vector2 penPos;
static bool didCollide;
void CollisionManager::DebugDraw(aie::Renderer2D* renderer)
{
	for (int i = 0; i < collisionObjects.size(); i++)
	{
		if (collisionObjects[i]->collider != nullptr)
		{
			AABB& aabb = collisionObjects[i]->collider->shapeAABB;
			renderer->SetRenderColour(1,1,0,1);
			renderer->DrawLine(aabb.min.x, aabb.min.y, aabb.max.x, aabb.min.y, 5);
			renderer->DrawLine(aabb.max.x, aabb.min.y, aabb.max.x, aabb.max.y, 5, 19);
			renderer->DrawLine(aabb.max.x, aabb.max.y, aabb.min.x, aabb.max.y, 5);
			renderer->DrawLine(aabb.min.x, aabb.min.y, aabb.min.x, aabb.max.y, 5);

			auto shape = (PolygonShape*)collisionObjects[i]->collider->shape;
			auto vertices = shape->GetGlobalVertices();
			for (int j = 0; j < shape->GetCount(); j++)
			{
				renderer->SetRenderColour(1, 0, 1, 1);
				renderer->DrawCircle(vertices[j].x, vertices[j].y, 5);
			}

			renderer->SetRenderColour(0, 1, 1, 1);
			renderer->DrawLine(penPos.x, penPos.y, (penPos + penetrationVector * 50).x, (penPos + penetrationVector * 50).y, 10);
		
		}
	}
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
			//check if the objects are compatible layer wise, if collider exists, and 
			if (collisionObjects[j]->collider != nullptr && collisionObjects[i]->collider->collisionLayer & collisionObjects[j]->collider->collisionMask
				&& collisionObjects[j]->collider->collisionLayer & collisionObjects[i]->collider->collisionMask)
			{
				//broad phase
				//this checks if the AABBs are colliding
				if (CheckAABBCollision(collisionObjects[i]->collider->shapeAABB, collisionObjects[j]->collider->shapeAABB))
				{
					std::cout << "AABBS!!!!!!!!!\n";
					//in this case we need to check if collision is valid, and if so, resolve it
					//we add it to collisions for this frame
					collisions.push_back(CollisionManifold(collisionObjects[i], collisionObjects[j]));
				}
				else
				{
					std::cout << "                \n";
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
	if (SetCollisionInfo(manifold))
	{
		////collision callbacks
		//manifold.a->actorObject->OnCollision(CollisionEvent{ manifold.b, manifold.collisionNormal, manifold.penetration });
		//manifold.b->actorObject->OnCollision(CollisionEvent{ manifold.a, manifold.collisionNormal, manifold.penetration });

		////resolve collision
		//Vector2 rV = manifold.b->GetVelocity() - manifold.a->GetVelocity();
		//float projectedRV = manifold.collisionNormal.GetDot(rV);
		//float impulseMagnitude = -(1 + std::min(manifold.a->collider->restitution, manifold.b->collider->restitution) * projectedRV) / (manifold.a->GetInverseMass() + manifold.b->GetInverseMass());
		//Vector2 impulse = manifold.collisionNormal * impulseMagnitude;

		//manifold.a->AddImpulse(impulse * -1);
		//manifold.b->AddImpulse(impulse);
	}
}

bool CollisionManager::CheckAABBCollision(AABB& a, AABB& b)
{
	return (a.min.x < b.max.x && a.min.y < b.max.y
		&& a.max.x > b.min.x && a.max.y > b.min.y
		&& b.min.x < a.max.x && b.min.y < a.max.y
		&& b.max.x > a.min.x && b.max.y > a.min.y);
}

bool CollisionManager::SetCollisionInfo(CollisionManifold& manifold)
{
	SetCollisionType(manifold);

	switch (manifold.type)
	{
	case CollisionType::CIRCLECIRCLE:
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//		CIRCLE-CIRCLE COLLISION
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		CircleShape* a = (CircleShape*)manifold.a->collider->shape;
		CircleShape* b = (CircleShape*)manifold.b->collider->shape;

		Vector2 delta = b->GetGlobalCentrePoint() - a->GetGlobalCentrePoint();
		float p = a->GetRadius() + b->GetRadius() - (delta).GetMagnitude();
		if (p > 0)
		{
			manifold.penetration = p;
			manifold.collisionNormal = delta.GetNormalised();
			return true;
		}
		else
		{
			return false;
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	break;
	case CollisionType::POLYGONCIRCLE:
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//		POLYGON-CIRCLE COLLISION
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		Vector2 normal;

		//polygon will be A
		PolygonShape* a = (PolygonShape*)manifold.a->collider->shape;
		CircleShape* b = (CircleShape*)manifold.b->collider->shape;
		auto polygonVertices = a->GetGlobalVertices();
		float pRadius = b->GetRadius() * b->GetRadius();
		int count = a->GetCount();

		//loop through all vertices and get the one with the min distance to the circle
		for (int i = 0; i < count; i++)
		{
			auto deltaVector = (polygonVertices[i] - b->GetGlobalCentrePoint());
			float dist = deltaVector.x * deltaVector.x + deltaVector.y * deltaVector.y;
			if (dist < pRadius)
			{
				pRadius = dist;
				normal = deltaVector;
			}
		}
		
		//return results
		if (pRadius < b->GetRadius() * b->GetRadius())
		{
			manifold.penetration = sqrtf(pRadius);
			manifold.collisionNormal = normal.GetNormalised();
			return true;
		}
		else
			return false;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
	}
	break;
	case CollisionType::POLYGONPOLYGON:
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//		POLYGON-POLYGON COLLISION
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		PolygonShape* a = (PolygonShape*)manifold.a->collider->shape;
		auto aVertices = a->GetGlobalVertices();
		auto aNormals = a->GetNormals();
		auto aCount = a->GetCount();

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
		penetrationVector = manifold.collisionNormal * manifold.penetration;
		penPos = manifold.a->actorObject->GetGlobalPosition();
		return true;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	break;
	}

	return false;
	
}

void CollisionManager::SetCollisionType(CollisionManifold& manifold)
{
	//CollisionType is equal to the two shape types added together
	manifold.type = (CollisionType)((char)manifold.a->GetCollider()->GetShape()->GetType() + (char)manifold.a->GetCollider()->GetShape()->GetType());

	if (manifold.type == CollisionType::POLYGONCIRCLE)
	{
		//make sure polygon is first
		if (manifold.a->GetCollider()->GetShape()->GetType() == ShapeType::CIRCLE)
		{
			auto circle = manifold.a;
			manifold.a = manifold.b;
			manifold.b = circle;
		}
	}
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
