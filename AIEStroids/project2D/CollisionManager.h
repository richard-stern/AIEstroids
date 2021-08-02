#pragma once
//Author: Connor

#include "PhysicsBody.h"
#include "Matrix3.h"
#include "Application.h"
#include <vector>
#include <forward_list>

struct CollisionEvent
{
	PhysicsBody* other;
	Vector2 collisionNormal;
	float penetration;
};

enum class CollisionType
{
	POLYGONPOLYGON,
	POLYGONCIRCLE,
	CIRCLECIRCLE
};
struct CollisionManifold
{
	CollisionManifold(PhysicsBody* a, PhysicsBody* b) : a(a), b(b) {}

	PhysicsBody* a;
	PhysicsBody* b;
	Vector2 collisionNormal;
	float penetration;
	CollisionType type;
};

struct MinMax
{
	float min;
	float max;
};

class CollisionManager
{
public:
	static void CreateInstance();
	static void DeleteInstance();
	static CollisionManager* GetInstance();

	//updates all physics bodies then resolves collisions
	void Update();
	//called by physics bodies to add themselves to the collision object list
	void AddBody(PhysicsBody* body);

private:
	static CollisionManager* instance;
	CollisionManager() = default;
	CollisionManager(CollisionManager&&) = default;
	CollisionManager(CollisionManager&) = default;

	//finds and resolves all collisions
	void ResolveCollisions();
	//resolve a specific manifold
	static void ResolveCollision(CollisionManifold& manifold);
	//check if AABBs are colliding
	static bool CheckAABBCollision(AABB& a, AABB& b);
	//returns whether objects have collided or not, also sets colliison normal and penetration in manifold
	static bool getCollisionInfo(CollisionManifold& manifold);
	//gets the minimum and maximum values of all vertices projected onto an axis
	//takes in local vertices
	static MinMax GetProjectedMinMax(Vector2& axis, Vector2* vertices, int vertexCount);

	std::vector<PhysicsBody*> collisionObjects;
	std::vector<CollisionManifold> collisions;
};

