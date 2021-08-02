#include "PhysicsBody.h"
#include "Actor.h"
#include "CollisionManager.h"

PhysicsBody::PhysicsBody(Actor* connectedGameObject, BodyType type, Collider* collider, float drag, float angularDrag, float mass)
	: actorObject(connectedGameObject), type(type), collider(collider), drag(drag), angularDrag(angularDrag), angularVelocity(0), velocity(Vector2()), force(Vector2()), torque(0)
{
	if (mass == 0)
	{
		if (collider != nullptr)
		{
			iMass = 1.0f / collider->CalculateMass();
		}
		else
		{
			iMass = 1;
		}
	}
	else
	{
		iMass = 1.0f / mass;
	}
}

void PhysicsBody::Update()
{
	switch (type)
	{
	case BodyType::DYNAMIC:
	{
		//set velocity based on force
		velocity += force * (PHYSICS_TIME_STEP * iMass);
		//add drag
		velocity -= velocity * (drag * PHYSICS_TIME_STEP);
		//set position
		actorObject->SetLocalPosition(actorObject->GetLocalPosition() + velocity * PHYSICS_TIME_STEP);

		//set angular velocity based on torque
		angularVelocity += torque * PHYSICS_TIME_STEP;
		//add drag
		angularVelocity -= angularVelocity * angularDrag * PHYSICS_TIME_STEP;
		//set rotation
		actorObject->SetRotationZ(actorObject->GetRotation() + angularVelocity * PHYSICS_TIME_STEP);
		
		//reset force
		force = Vector2::ZERO();
	}
		break;
	case BodyType::KINEMATIC:
	{
		//add drag
		velocity -= velocity * (drag * PHYSICS_TIME_STEP);
		//set position
		actorObject->SetLocalPosition(actorObject->GetLocalPosition() + velocity * PHYSICS_TIME_STEP);

		//add drag
		angularVelocity -= angularVelocity * angularDrag * PHYSICS_TIME_STEP;
		//set rotation
		actorObject->SetRotationZ(actorObject->GetRotation() + angularVelocity * PHYSICS_TIME_STEP);
	}
		break;
	case BodyType::STATIC:
		break;
	}
	
	if (collider != nullptr)
		UpdateAABB();
}

void PhysicsBody::AddImpulse(Vector2 impulse)
{
	//same as add velocity except impacted by mass
	velocity += impulse * iMass;
}

void PhysicsBody::UpdateAABB()
{
	auto& aabb = collider->shapeAABB;

	switch (collider->shape->getType())
	{
	case ShapeType::CIRCLE:
	{
		//aabb.topLeft = 
	}
		break;
	case ShapeType::POLYGON:
		break;
		{
			PolygonShape* colliderShape = (PolygonShape*)collider->shape;

			//maxX
			aabb.bottomRight.x = INFINITY;
			//maxY
			aabb.bottomRight.y = INFINITY;
			//minX
			aabb.topLeft.x = -INFINITY;
			//minY
			aabb.topLeft.y = -INFINITY;

			for (int i = 0; i < colliderShape->count; i++)
			{
				auto& vertex = colliderShape->vertices[i];
				
				//set maxX
				if (vertex.x > aabb.bottomRight.x)
					aabb.bottomRight.x = vertex.x;
				//set minX
				if (vertex.x < aabb.topLeft.x)
					aabb.topLeft.x = vertex.x;

				//set maxY
				if (vertex.y > aabb.bottomRight.y)
					aabb.bottomRight.y = vertex.y;
				//set minY
				if (vertex.y < aabb.topLeft.y)
					aabb.topLeft.y = vertex.y;
			}

			aabb.topLeft += actorObject->GetGlobalPosition();
			aabb.bottomRight += actorObject->GetGlobalPosition();
		}
	}
	
}
