#pragma once
#include <stdlib.h>
#include <time.h>
#include "Matrix3.h"
#include "Vector2.h"
#include "Actor.h"

class Player;

class Enemy : public Actor
{
private:
	bool m_destroyed;
	Player* m_player;
	Vector2 m_position;

public:
	Enemy();
	~Enemy();
	void Update(float deltaTime) override;
	void Draw(aie::Renderer2D* renderer) override;
	void OnCollision(GameObject* other);
	bool IsDestroyed() { return m_destroyed; }
	Vector2 GetPosition();

private:
	void Seek(float deltaTime);
	void SetRandomLocation();
	Matrix3 GetRandomLocation();
};