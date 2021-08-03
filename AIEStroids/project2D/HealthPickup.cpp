#include "HealthPickup.h"
#include "CollisionLayers.h"
#include "TextureManager.h"

HealthPickup::HealthPickup(int health, const char* textureName) : Actor(/*textureName*/)
{
	m_healthGained = health;
	SetWrapAndRespawn(true);
	TextureManager::Get()->LoadTexture(textureName);
	
	//Set a random velocity at start

	//Create a physics body
	//Set physics body
}

HealthPickup::~HealthPickup()
{
	//Delete physics body
}

void HealthPickup::OnCollision(CollisionEvent _event)
{
	//If collides with player, add to player health and destroy this object

	/*CollisionLayer colLayer = _event.other->GetCollider()->GetCollisionLayer();
	switch (colLayer)
	{
	case CollisionLayer::PLAYER:
		Actor* actor = _event.other->GetActor();
		actor->SetHealth(actor->GetHealth() + m_healthGained);
		m_IsActive = false;
		break;

	case CollisionLayer::ROCK:
		break;
	case CollisionLayer::BULLET:
		m_IsActive = false;
		break;
	case CollisionLayer::ENEMY:
		break;
	}*/

	//If collides with bullet, destroyt this object

	//If collides with rocks or enemies, they should bounce off without damaging either
	
	//When destroying this object, just set its m_bVisible to false
}
