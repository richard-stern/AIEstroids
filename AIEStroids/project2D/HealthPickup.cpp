#include "HealthPickup.h"

HealthPickup::HealthPickup(int health, const char* textureName) : Actor(/*textureName*/)
{
	m_healthGained = health;
	//m_bWrapAndRespawn = true;
	//Set a random velocity at start
}

HealthPickup::~HealthPickup()
{

}

void HealthPickup::OnCollision(CollisionEvent _event)
{
	//If collides with player, add to player health and destroy this object

	//If collides with bullet, destroyt this object

	//If collides with rocks or enemies, they should bounce off without damaging either

	//When destroying this object, just set its m_bVisible to false
}
