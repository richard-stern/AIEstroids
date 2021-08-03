/*
 * Author: Paul King
*/

#pragma once
#include <stdlib.h>
#include <time.h>
#include "Matrix3.h"
#include "Vector2.h"
#include "Actor.h"

class Player;
class Level;
class Rock;

#define MAX_ENEMY_VELOCITY 10

class Enemy : public Actor
{
private:
	bool m_destroyed;
	Player* m_player;
	const float MAX_SEE_AHEAD = 10.0f;
	const float MAX_AVOID_FORCE = 1.0f;
	Rock** m_rocks;
	unsigned int m_Health;

public:
	Enemy(Player* player, Rock** rocks);
	Enemy(Vector2 pos, Player* player, Rock** rocks);
	~Enemy();
	void Update(float deltaTime) override;
	void Draw(aie::Renderer2D* renderer) override;
	void OnCollision(GameObject* other);
	bool IsDestroyed() { return m_destroyed; }
	Vector2 GetPosition();

private:
	void Seek(float deltaTime);
	void Pursue(float deltaTime);
	void AvoidObstacles(float deltaTime);
	void SetRandomLocation();
	Matrix3 GetRandomLocation();
	Vector2 CollisionAvoidance();
	GameObject* FindMostThreateningObstacle();
	bool LineIntersectsCircle(Vector2 a, Vector2 b, GameObject* obstacle);
};