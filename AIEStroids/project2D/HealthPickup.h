#pragma once
#include "Actor.h"
class HealthPickup :	public Actor
{
public:
	HealthPickup(int health);
	~HealthPickup();

	void OnCollision(CollisionEvent _event) override;
	void Update(float deltaTime) override;
private:
	int m_healthGained;
	Vector2 randomVelocity;
};

