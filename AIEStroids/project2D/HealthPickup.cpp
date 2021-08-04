//Written by Jayden Hunter
//		-- Get Outta 'Ere
#include "HealthPickup.h"
#include "CollisionLayers.h"
#include "TextureManager.h"

HealthPickup::HealthPickup(int health) : Actor(/*textureName*/)
{
	m_healthGained = health;
	SetWrapAndRespawn(true);
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/car.png");

	GeneratePhysicsBody(32, 32, CollisionLayer::PICKUP, (unsigned int)CollisionLayer::ALL);

	//Set a random velocity at start
	randomVelocity = Vector2(rand() % 1000, rand() % 1000);
	randomVelocity = randomVelocity.GetNormalised();
	Vector2 direction(((rand() % 200) - 100) / 100.0f, ((rand() % 200) - 100) / 100.0f);

	m_PhysicsBody->SetVelocity(direction.GetNormalised() *100);
	m_PhysicsBody->SetAngularVelocity((rand() % 5) - 2.5);

	Vector2 pos = Vector2(rand() % 1000, rand() % 1000);
	SetPosition(pos);
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
		if (actor && m_IsActive)
		{
			actor->SetHealth(actor->GetHealth() + m_healthGained);
			SetActive(false);
		}
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
		SetActive(false);
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

void HealthPickup::Update(float deltaTime)
{
	Actor::Update(deltaTime);
}
