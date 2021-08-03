#include "CollisionManager.h"
#include "Actor.h"
#include "Input.h"
#include <iostream>

CollisionManager* CollisionManager::instance = nullptr;

void CollisionManager::Update()
{
	if (aie::Input::GetInstance()->WasKeyPressed(aie::INPUT_KEY_C))
	{
		drawDebug = !drawDebug;
	}

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

void CollisionManager::DebugDraw(aie::Renderer2D* renderer)
{
	if (drawDebug)
	{
		for (int i = 0; i < collisionObjects.size(); i++)
		{
			if (collisionObjects[i]->collider != nullptr)
			{
				//Draw AABB
				AABB& aabb = collisionObjects[i]->collider->shapeAABB;
				renderer->SetRenderColour(1, 1, 0, 1);
				renderer->DrawLine(aabb.min.x, aabb.min.y, aabb.max.x, aabb.min.y, 1.5f);
				renderer->DrawLine(aabb.max.x, aabb.min.y, aabb.max.x, aabb.max.y, 1.5f, 19);
				renderer->DrawLine(aabb.max.x, aabb.max.y, aabb.min.x, aabb.max.y, 1.5f);
				renderer->DrawLine(aabb.min.x, aabb.min.y, aabb.min.x, aabb.max.y, 1.5f);

				//Draw Shape
				switch (collisionObjects[i]->collider->shape->GetType())
				{
				case ShapeType::CIRCLE:
					{
						//just draw as a high point count polygon
						auto shape = (CircleShape*)collisionObjects[i]->collider->shape;
						Vector2 position = shape->GetGlobalCentrePoint();
						renderer->SetRenderColour(1, 0, 1, 1);
						float rotationAmount = (float)M_PI / 10.0f;
						for (int j = 0; j < 19; j++)
						{
							Vector2 straightLine = Vector2::RIGHT() * shape->GetRadius();
							Vector2 straightLine2 = Vector2::RIGHT() * shape->GetRadius();
							straightLine.SetRotation(rotationAmount * j);
							straightLine2.SetRotation(rotationAmount * (j + 1));
							renderer->DrawLine(straightLine.x + position.x, straightLine.y + position.y, straightLine2.x + position.x, straightLine2.y + position.y, 3);
						}
						Vector2 straightLine = Vector2::RIGHT() * shape->GetRadius();
						Vector2 straightLine2 = Vector2::RIGHT() * shape->GetRadius();
						straightLine2.SetRotation(rotationAmount * (19));
						renderer->DrawLine(straightLine.x + position.x, straightLine.y + position.y, straightLine2.x + position.x, straightLine2.y + position.y, 3);
					}

					break;
				case ShapeType::POLYGON:
					{
						auto shape = (PolygonShape*)collisionObjects[i]->collider->shape;
						auto vertices = shape->GetGlobalVertices();
						renderer->SetRenderColour(1, 0, 1, 1);
						for (int j = 0; j < shape->GetCount() - 1; j++)
						{
							renderer->DrawLine(vertices[j].x, vertices[j].y, vertices[j + 1].x, vertices[j + 1].y, 3);
							renderer->DrawCircle(vertices[j].x, vertices[j].y, 5);
						}
						renderer->DrawLine(vertices[0].x, vertices[0].y, vertices[shape->GetCount() - 1].x, vertices[shape->GetCount() - 1].y, 3);
						renderer->DrawCircle(vertices[shape->GetCount() - 1].x, vertices[shape->GetCount() - 1].y, 5);
					}

					break;
				}
			}
		}
		//go through all the collisions that happened last time and draw penetration vector
		for (int i = 0; i < collisions.size(); i++)
		{
			renderer->SetRenderColour(0, 1, 1, 1);
			auto pos = collisions[i].b->actorObject->GetPosition();
			auto pen = collisions[i].collisionNormal * 100;
			renderer->DrawLine(pos.x, pos.y, pos.x + pen.x, pos.y + pen.y, 5);
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

		for (int j = i + 1; j < collisionObjects.size(); j++)
		{
			//check if the objects are compatible layer wise, if collider exists, and 
			if (collisionObjects[j]->collider != nullptr && collisionObjects[i]->collider->collisionLayer & collisionObjects[j]->collider->collisionMask
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
	if (SetCollisionInfo(manifold))
	{
		//collision callbacks
		manifold.a->actorObject->OnCollision(CollisionEvent{ manifold.b, manifold.collisionNormal, manifold.penetration });
		manifold.b->actorObject->OnCollision(CollisionEvent{ manifold.a, manifold.collisionNormal, manifold.penetration });

		//resolve collision
		Vector2 rV = manifold.b->GetVelocity() - manifold.a->GetVelocity();
		float projectedRV = manifold.collisionNormal.GetDot(rV);
		//velocities are seperating
		if (projectedRV > 0)
		{
			return;
		}
		//BREAKING THIS DOWN INTO IT'S PARTS TO TRY TO FIND THE PROBLEM
		//bounce factor (minimum of the two in this case)
		float restitution = std::min(manifold.a->collider->restitution, manifold.b->collider->restitution);
		//the impulse magnitude
		float impulseMagnitude = -(1 + restitution * projectedRV);
		//divide by inverse masses add together as a way to ratio by mass (AddImpulse timeses by inverse mass)
		impulseMagnitude /= (manifold.a->GetInverseMass() + manifold.b->GetInverseMass());
		//turn into vector
		Vector2 impulse = manifold.collisionNormal * impulseMagnitude;

		manifold.a->AddImpulse(impulse* -1);
		manifold.b->AddImpulse(impulse);
		if (manifold.a->type == BodyType::DYNAMIC)
			manifold.a->GetActor()->SetPosition(manifold.a->GetActor()->GetPosition() + manifold.collisionNormal * (manifold.penetration / (manifold.a->GetInverseMass() + manifold.b->GetInverseMass()) * manifold.a->GetInverseMass()));
		if (manifold.b->type == BodyType::DYNAMIC)
			manifold.b->GetActor()->SetPosition(manifold.b->GetActor()->GetPosition() + manifold.collisionNormal * (-manifold.penetration / (manifold.a->GetInverseMass() + manifold.b->GetInverseMass()) * manifold.b->GetInverseMass()));
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
		float p = -INFINITY;
		int count = a->GetCount();

		//loop through all vertices and get the one with the min distance to the circle
		for (int i = 0; i < count; i++)
		{
			auto deltaVector = (b->GetGlobalCentrePoint() - polygonVertices[i]);
			float dist = deltaVector.GetMagnitude();
			float potentialP = b->GetRadius() - dist;
			if (potentialP > 0 && potentialP > p )
			{
				p = potentialP;
				normal = deltaVector;
			}
		}
		
		//return results
		if (!isinf(p))
		{
			manifold.penetration = p;
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
		auto aGlobal = manifold.a->GetActor()->GetGlobalTransform();
		auto aCount = a->GetCount();

		PolygonShape* b = (PolygonShape*)manifold.b->collider->shape;
		auto bVertices = b->GetGlobalVertices();
		auto bNormals = ((PolygonShape*)manifold.b->collider->shape)->GetNormals();
		auto bGlobal = manifold.b->GetActor()->GetGlobalTransform();
		auto bCount = b->GetCount();
		Vector2 bCentre = b->GetGlobalCentrePoint();

		//the projection data
		float penetration = INFINITY;
		float absPenetration = INFINITY;
		Vector2 pNormal;
		Vector2 deltaAB = b->GetGlobalCentrePoint() - a->GetGlobalCentrePoint();

		//loop through a's normals
		for (int i = 0; i < aCount; i++)
		{
			//get minimum and maximum on this axis
			auto axis = aNormals[i] * aGlobal;
			MinMax aResult = GetProjectedMinMax(axis, aVertices, aCount);
			MinMax bResult = GetProjectedMinMax(axis, bVertices, bCount);

			//check if colliding (on this axis)
			if ((aResult.min < bResult.max && aResult.max > bResult.min))
			{
				//need to get distance between maximum and minimum
				float length = abs(std::max(aResult.max, bResult.max) - std::min(aResult.min, bResult.min));
				//then get the size of the shapes on the axis
				//pvalue equals total size of both shapes - length between both shapes 
				float pValue = -(aResult.max - bResult.min);
				absPenetration = abs(pValue);
				//if smallest penetration, set it to penetration vector
				if (absPenetration < penetration)
				{
					penetration = absPenetration;
					pNormal = axis * pValue;
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
			auto axis = bNormals[i] * bGlobal;
			MinMax aResult = GetProjectedMinMax(axis, aVertices, aCount);
			MinMax bResult = GetProjectedMinMax(axis, bVertices, bCount);

			//check if colliding (on this axis)
			if ((aResult.min < bResult.max && aResult.max > bResult.min))
			{
				//need to get distance between maximum and minimum
				float length = abs(std::max(aResult.max, bResult.max) - std::min(aResult.min, bResult.min));
				//then get the size of the shapes on the axis
				//pvalue equals total size of both shapes - length between both shapes 
				float pValue = -(aResult.max - bResult.min);
				absPenetration = abs(pValue);
				//if smallest penetration, set it to penetration vector
				if (absPenetration < penetration)
				{
					penetration = absPenetration;
					pNormal = axis * pValue;
				}
			}
			//if not they are not colliding, so return
			else
				return false;
		}

		//if reached this point without exiting, they are colliding.
		//set penetration data in manifold
		manifold.penetration = penetration;
		manifold.collisionNormal = pNormal.GetNormalised();
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
	manifold.type = (CollisionType)((char)manifold.a->GetCollider()->GetShape()->GetType() + (char)manifold.b->GetCollider()->GetShape()->GetType());

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
