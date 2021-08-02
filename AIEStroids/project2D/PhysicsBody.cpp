#include "PhysicsBody.h"
#include "Actor.h"
#include "CollisionManager.h"

PhysicsBody::PhysicsBody(Actor* connectedGameObject, BodyType type, Collider* collider, float drag, float angularDrag, float mass)
	: actorObject(connectedGameObject), type(type), collider(collider), drag(drag), angularDrag(angularDrag)
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

		UpdateAABB();
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
		
		UpdateAABB();
	}
		break;
	case BodyType::STATIC:
	{
		UpdateAABB();
	}
		break;
	}
}

void PhysicsBody::AddImpulse(Vector2 impulse)
{
	//same as add velocity except impacted by mass
	velocity += impulse * iMass;
}

void PhysicsBody::UpdateAABB()
{
	auto& aabb = collider->shapeAABB;
	//maxX
	aabb.bottomRight.x = INFINITY;
	//maxY
	aabb.bottomRight.y = INFINITY;
	//minX
	aabb.topLeft.x = -INFINITY;
	//minY
	aabb.topLeft.y = -INFINITY;
	
	for (int i = 0; i < collider->shape->count; i++)
	{
		auto& vertex = collider->shape->vertices[i];
	}
}
