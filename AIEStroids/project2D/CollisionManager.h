#pragma once
//Author: Connor

#include "PhysicsBody.h"
#include "Matrix3.h"
#include "Application.h"
#include <vector>
#include <forward_list>
#include "Renderer2D.h"

struct CollisionEvent
{
	PhysicsBody* other;
	Vector2 collisionNormal;
	float penetration;
};

enum class CollisionType
{
	CIRCLECIRCLE,
	POLYGONCIRCLE,
	POLYGONPOLYGON
};

struct CollisionManifold
{
	//penetration and type definitions are just there to clear up warnings, they will be immediately overwritten
	CollisionManifold(PhysicsBody* a, PhysicsBody* b) : a(a), b(b) { penetration = 0; type = (CollisionType)0; }

	PhysicsBody* a;
	PhysicsBody* b;
	Vector2 collisionNormal;
	float penetration;
	CollisionType type;
};

//just a pair of floats
//used internally for collision
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
	//called by physics body to remove self from list (expensive!!)
	void RemoveBody(PhysicsBody* body);

	void DebugDraw(aie::Renderer2D* renderer);

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
	static bool SetCollisionInfo(CollisionManifold& manifold);
	//gets the minimum and maximum values of all vertices projected onto an axis
	static void SetCollisionType(CollisionManifold& manifold);
	//takes in local vertices
	static MinMax GetProjectedMinMax(Vector2& axis, Vector2* vertices, int vertexCount);

	std::vector<PhysicsBody*> collisionObjects;
	std::vector<CollisionManifold> collisions;
	bool drawDebug = false;
};

