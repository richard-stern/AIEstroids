/*
 * Author: Paul King
*/

#pragma once
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix3.h"
#include "Vector2.h"
#include "Actor.h"

class Player;
class Level;
class Rock;

#define SPRITE_SIZE 128
#define MAX_ENEMY_VELOCITY 200

class Enemy : public Actor
{
private:
	bool m_destroyed;
	Player* m_player;	
	Rock** m_rocks;	
	Vector2 steeringForce;

public:
	Enemy(Player* player, Rock** rocks);
	Enemy(Vector2 pos, Player* player, Rock** rocks);
	~Enemy();
	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent event) override;
	bool IsDestroyed() { return (m_CurrentHealth <= 0); }

	const float MAX_SEE_AHEAD = 100.0f;
	const float MAX_AVOID_FORCE = 10.0f;
	const int MIN_AVOID_DISTANCE = 120;

private:
	void Seek(Actor* target, float deltaTime);
	void Pursue(float deltaTime);
	void SetRandomLocation();
	void CollisionAvoidance(float deltaTime);
	GameObject* FindMostThreateningObstacle(Vector2 ahead, Vector2 ahead2);
	bool LineIntersectsCircle(Vector2 a, Vector2 b, GameObject* obstacle);
};