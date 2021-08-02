#pragma once
#include "Actor.h"
class HealthPickup :	public Actor
{
public:
	HealthPickup(int health,const char* textureName);
	~HealthPickup();

private:
	int m_healthGained;
};

