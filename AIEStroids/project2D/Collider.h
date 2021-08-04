//Author: Connor

#pragma once
#include "Vector2.h"
#include "Shape.h"
class PhysicsBody;
class CollisionManager;

class Collider
{
public:
	Collider(Shape* shape, unsigned short collisionLayer, unsigned short collisionMask, float density = 1, float restitution = 0, bool isTrigger = false);
	float CalculateMass();
	
	Shape* GetShape() { return shape; };
	AABB* GetAABB() { return &shapeAABB; }
	unsigned short GetCollisionLayer() { return collisionLayer; }
	unsigned short GetCollisionMask() { return collisionMask; }
	float GetDensity() { return density; }
	bool GetTrigger() { return trigger; }

	void SetCollisionLayer(unsigned short layer) { collisionLayer = layer; };
	void SetCollisionMask(unsigned short mask) { collisionMask = mask; }
	void SetRestitution(float restitution) { this->restitution = restitution; }
	void SetTrigger(bool trigger) { this->trigger = trigger; }

	Collider(const Collider& other) = delete;
	Collider(Collider&& other) = delete;
	Collider& operator=(const Collider& other) = delete;
	Collider& operator=(Collider&& other) = delete;
	~Collider();
private:
	friend PhysicsBody;
	friend CollisionManager;

	Shape* shape;
	AABB shapeAABB;
	unsigned short collisionLayer;
	unsigned short collisionMask;
	//bounciness
	float restitution;
	float density;
	bool trigger;
};

