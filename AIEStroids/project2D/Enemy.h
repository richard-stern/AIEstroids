#pragma once
#include <stdlib.h>
#include <time.h>

class GameObeject;
class Actor;

class Enemy : public Actor
{
private:
	bool m_destroyed;
public:
	Enemy();
	~Enemy();
	void Update();
	void Draw();
	void OnCollision(GameObject other);

private:
	void Seek();
	Matrix3 GetRandomLocation();
};