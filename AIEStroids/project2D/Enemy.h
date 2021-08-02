#pragma once
#include <stdlib.h>
#include <time.h>
#include "Matrix3.h"
#include "Vector2.h"

class GameObject;
class Actor;

class Enemy : public Actor,
{
private:
	bool m_destroyed;
	Player* m_player;
	Vector2 m_position;

public:
	Enemy();
	~Enemy();
	void Update(float deltaTime) override;
	void Draw(aie::Renderer2D* renderer);
	void OnCollision(GameObject* other);
	bool IsDestroyed() { return m_destroyed; }

private:
	void Seek(float deltaTime);
	void SetRandomLocation();
	Matrix3 GetRandomLocation();
};