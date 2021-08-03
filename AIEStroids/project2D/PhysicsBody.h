//Author: Connor

#pragma once
#include "Vector2.h"
#include "Collider.h"
#include <algorithm>

constexpr float PHYSICS_TIME_STEP = 1.0f / 60;

class Actor;
class CollisionManager;

enum class BodyType : char
{
	STATIC,
	KINEMATIC,
	DYNAMIC
};
// static: zero mass, zero velocity, may be manually moved
// kinematic: zero mass, non-zero velocity set by user, moved by collisionManager
// dynamic: positive mass, non-zero velocity determined by forces, moved by collisionManager

class PhysicsBody
{
public:
	//if you don't input a value for mass it will be automatically calculated based on shape
	PhysicsBody(Actor* connectedGameObject, BodyType type, Collider* collider = nullptr, float drag = 0, float angularDrag = 0, float mass = 0, bool addToManager = true);

	void Update(float deltaTime);

	//getters
	Actor*	GetActor()			{ return actorObject; }
	Collider*	GetCollider()			{ return collider; }
	Vector2		GetVelocity()			{ return velocity; }
	Vector2		GetForce()				{ return velocity; }
	float		GetDrag()				{ return drag; }
	float		GetAngularVelocity()	{ return angularVelocity; }
	float		GetTorque()				{ return torque; }
	float		GetAngularDrag()		{ return angularDrag; }
	float		GetInverseMass()		{ return iMass; }
	float		GetMass() { return 1.0f/iMass; }
	Actor*		GetConnectedActor() { return actorObject; }
	BodyType	GetType() { return type; }

	//setters
	void SetVelocity(Vector2 vel)		{ velocity = vel; }
	void SetForce(Vector2 force)		{ this->force = force; }
	void SetDrag(float drag)			{ this->drag = drag * PHYSICS_TIME_STEP < 1 ? drag : 1; }
	void SetAngularVelocity(float aVel) { angularVelocity = angularVelocity; }
	void SetTorque(float torque)		{ this->torque = torque; }
	void SetAngularDrag(float aDrag)	{ angularDrag = aDrag * PHYSICS_TIME_STEP < 1 ? angularDrag : 1; }
	void SetMass(float mass)			{ iMass = 1.0f / mass; }
	void SetType(BodyType type)			{ this->type = type; }
	
	//adders
	void AddImpulse(Vector2 impulse);
	void AddVelocity(Vector2 vel) { velocity += vel; }
	void AddForce(Vector2 force) { this->force += force; }
	void AddAngularVelocity(float aVel) { angularVelocity += aVel; }
	void AddTorque(float torque) { this->torque += torque; }

	void UpdateAABB();

private:
	friend CollisionManager;
	//Connected GameObject
	Actor* actorObject;
	Collider* collider;
	Vector2 velocity;
	Vector2 force;

	float angularVelocity;
	float torque;
	float drag;
	float angularDrag;
	float iMass;

	BodyType type;
};

