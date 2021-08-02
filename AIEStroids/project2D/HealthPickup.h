#pragma once
#include "Actor.h"
class HealthPickup :	public Actor
{
public:
	HealthPickup(int health,const char* textureName);
	~HealthPickup();

	void OnCollision(CollisionEvent _event) override;

private:
	int m_healthGained;
};

