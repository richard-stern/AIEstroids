#include "HealthPickup.h"

HealthPickup::HealthPickup(int health, const char* textureName) : Actor(/*textureName*/)
{
	m_healthGained = health;
}

HealthPickup::~HealthPickup()
{
}
