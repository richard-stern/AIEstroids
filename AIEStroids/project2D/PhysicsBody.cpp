#include "PhysicsBody.h"
#include "Actor.h"
#include "CollisionManager.h"

PhysicsBody::PhysicsBody(Actor* connectedGameObject, BodyType type, Collider* collider, float drag, float angularDrag, float mass, bool addToManager)
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

	if (addToManager)
	{
		CollisionManager::GetInstance()->AddBody(this);
	}

}

PhysicsBody::~PhysicsBody()
{
	CollisionManager::GetInstance()->RemoveBody(this);
	delete collider;
}

void PhysicsBody::Update(float deltaTime)
{
	switch (type)
	{
	case BodyType::DYNAMIC:
	{
		//set velocity based on force
		velocity += force * (deltaTime * iMass);
		//add drag
		velocity -= velocity * (drag * deltaTime);
		//set position
		actorObject->SetLocalPosition(actorObject->GetLocalPosition() + velocity * deltaTime);

		//set angular velocity based on torque
		angularVelocity += torque * deltaTime;
		//add drag
		angularVelocity -= angularVelocity * angularDrag * deltaTime;
		//set rotation
		actorObject->SetRotation(actorObject->GetRotation() + angularVelocity * deltaTime);
		
		//reset force
		force = Vector2::ZERO();
	}
		break;
	case BodyType::KINEMATIC:
	{
		//set position
		actorObject->SetLocalPosition(actorObject->GetLocalPosition() + velocity * deltaTime);

		//set rotation
		actorObject->SetRotation(actorObject->GetRotation() + angularVelocity * deltaTime);
	}
		break;
	case BodyType::STATIC:
		break;
	}
	
	//finally update global shape points and AABB
	if (collider != nullptr)
	{
		collider->GetShape()->CalculateGlobal(actorObject->GetGlobalTransform());
		UpdateAABB();
	}
}

void PhysicsBody::AddImpulse(Vector2 impulse)
{
	//same as add velocity except impacted by mass
	if (type != BodyType::KINEMATIC)
		velocity += impulse * iMass;
}

void PhysicsBody::UpdateAABB()
{
	auto& aabb = collider->shapeAABB;

	switch (collider->shape->GetType())
	{
	case ShapeType::CIRCLE:
	{
		CircleShape* circleShape = (CircleShape*)collider->shape;
		float radius = circleShape->GetRadius();

		//aabb.bottomRight.x = radius + 
	}
		break;
	case ShapeType::POLYGON:
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

		//get global vertices
		auto vertices = colliderShape->GetGlobalVertices();

		for (int i = 0; i < colliderShape->GetCount(); i++)
		{
				
			//set maxX
			if (vertices[i].x > aabb.bottomRight.x)
				aabb.bottomRight.x = vertices[i].x;
			//set minX
			if (vertices[i].x < aabb.topLeft.x)
				aabb.topLeft.x = vertices[i].x;

			//set maxY
			if (vertices[i].y > aabb.bottomRight.y)
				aabb.bottomRight.y = vertices[i].y;
			//set minY
			if (vertices[i].y < aabb.topLeft.y)
				aabb.topLeft.y = vertices[i].y;
		}
	}
		break;
	}
	
}
