#pragma once
#include "Vector2.h"
#include "Collider.h"
#include <algorithm>

constexpr float PHYSICS_TIME_STEP = 1.0f / 60;

class Actor;

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
	PhysicsBody(Actor* connectedGameObject, BodyType type, Collider* collider = nullptr, float drag = 0, float angularDrag = 0, float mass = 0);
	void Update();

	//getters
	Collider*	getCollider()			{ return collider; }
	Vector2		getVelocity()			{ return velocity; }
	Vector2		getForce()				{ return velocity; }
	float		getDrag()				{ return drag; }
	float		getAngularVelocity()	{ return angularVelocity; }
	float		getTorque()				{ return torque; }
	float		getAngularDrag()		{ return angularDrag; }
	float		getInverseMass()		{ return iMass; }
	float		getMass() { return 1.0f/iMass; }
	Actor* getConnectedActor() { return actorObject; }
	BodyType	getType() { return type; }

	//setters
	void setVelocity(Vector2 vel)		{ velocity = vel; }
	void setForce(Vector2 force)		{ this->force = force; }
	void setDrag(float drag)			{ this->drag = drag * PHYSICS_TIME_STEP < 1 ? drag : 1; }
	void setAngularVelocity(float aVel) { angularVelocity = angularVelocity; }
	void setTorque(float torque)		{ this->torque = torque; }
	void setAngularDrag(float aDrag)	{ angularDrag = aDrag * PHYSICS_TIME_STEP < 1 ? angularDrag : 1; }
	void setMass(float mass)			{ iMass = 1.0f / mass; }
	void setType(BodyType type)			{ this->type = type; }
	
	//adders
	void addImpulse(Vector2 impulse);
	void addVelocity(Vector2 vel) { velocity += vel; }
	void addForce(Vector2 force) { this->force += force; }
	void addAngularVelocity(float aVel) { angularVelocity += aVel; }
	void addTorque(float torque) { this->torque += torque; }

	void updateAABB();

private:
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

