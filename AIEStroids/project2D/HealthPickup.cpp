//Written by Jayden Hunter
//		-- Get Outta 'Ere
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
	//Try get actor
	Actor* actor = _event.other->GetActor();

	//Return out if actor is null
	if (!actor)
		return;

	//Get the layer the actor is on
	unsigned short colLayer = _event.other->GetCollider()->GetCollisionLayer();

	//Cast Short To Enum
	switch ((CollisionLayer)colLayer)
	{

	//Handle Player Collision
	case CollisionLayer::PLAYER:
	{
		if (actor)
			actor->SetHealth(actor->GetHealth() + m_healthGained);
		m_IsActive = false;
	}
	break;

	//Handle Rock Collision
	case CollisionLayer::ROCK:
	{
		Actor* actor = _event.other->GetActor();

		//BOUNCE OFF 
	}
	break;

	//Handle Bullet Collision
	case CollisionLayer::BULLET:
	{
		m_IsActive = false;
	}
	break;

	//Handle Enemy Collision
	case CollisionLayer::ENEMY:
	{
		Actor* actor = _event.other->GetActor();
		//BOUNCE OFF 
	}
	break;
	}

	//If collides with player, add to player health and destroy this object
	//If collides with bullet, destroyt this object

	//If collides with rocks or enemies, they should bounce off without damaging either

	//When destroying this object, just set its m_bVisible to false
}
