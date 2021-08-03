#include "Player.h"
#include "Application.h"
#include "GUI.h"
#include <cmath>
#include "TextureManager.h"
#include "CollisionLayers.h"

//Author Rahul J. (BEANMEISTER)

Player::Player(Vector2 startPos) : Actor::Actor(startPos)
{
	//Player shouldn't wrap
	m_WrapAndRespawn = false;

	//Assign ship texture
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/ship.png");
	
	//--------- COLLIDER GENERATION ----------------------//
	//Create a box that is the same dimensions as the texture
	Shape* shape = PolygonShape::CreateBox(m_Texture->GetWidth() / 2.0f, m_Texture->GetHeight() / 2.0f, Vector2::ZERO());
	//Collide with everything but player
	unsigned int layermask = (unsigned int)CollisionLayer::ALL ^ (unsigned int)CollisionLayer::PLAYER;
	//Create collider
	Collider* collider = new Collider(shape, (unsigned short)CollisionLayer::PLAYER, layermask);
	//Create the physics body using the generated collider
	m_PhysicsBody = (new PhysicsBody(this, BodyType::DYNAMIC, collider));
	//Don't be in the corner
	SetPosition(Vector2::ONE() * 100.0f);
	gui = GUI::GetInstance();
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	if (playerAlive)
	{

		//Calculate input vectors
		//------------------------------------
		// 	  + Y
		// -X  +  +X
		//    - Y
		Vector2 inputVector(0.0f, 0.0f);
		aie::Input* input = aie::Input::GetInstance();
		//Get input
		if (input->IsKeyDown(PLAYER_INPUT_UP))
			inputVector.y++;
		if (input->IsKeyDown(PLAYER_INPUT_DOWN))
			inputVector.y--;
		if (input->IsKeyDown(PLAYER_INPUT_RIGHT))
			inputVector.x++;
		if (input->IsKeyDown(PLAYER_INPUT_LEFT))
			inputVector.x--;

		//Store current velocity
		Vector2 currentVelocity = m_PhysicsBody->GetVelocity();
		float currentAngularVelocity = m_PhysicsBody->GetAngularVelocity();

		//Get direction that the player is facing
		Vector2 playerForward = m_GlobalTransform.GetRight();

		//Base thrust amount without any modification
		float thrustAmount = PLAYER_THRUST;
		float torqueAmount = PLAYER_TORQUE * DEG2RAD;

		//Scale the thrust amount if the player is facing away from their current velocity, helps with responsiveness
		if (Vector2::Dot(playerForward, currentVelocity) < 0)
			thrustAmount *= PLAYER_COUNTERFORCE_MULT;

		//Scale up torque amount if rotating away from current rotational velocity
		if (currentAngularVelocity * inputVector.x < 0)
			torqueAmount *= PLAYER_COUNTERTORQUE_MULT;

		//--------------
		//	Add forces
		//--------------
		m_PhysicsBody->AddForce(playerForward * std::abs(inputVector.y) * thrustAmount * deltaTime);
		//Limit player speed
		currentVelocity = m_PhysicsBody->GetVelocity();
		if (currentVelocity.GetMagnitude() > PLAYER_MAXSPEED)
			currentVelocity = currentVelocity.GetNormalised() * PLAYER_MAXSPEED;

		m_PhysicsBody->AddTorque(inputVector.x * torqueAmount * deltaTime);
		//Limit angular velocity
		currentAngularVelocity = m_PhysicsBody->GetAngularVelocity();
		float absoluteValue = std::abs(currentAngularVelocity);
		if (absoluteValue > PLAYER_MAXROTATIONSPEED)
			//Dividing angular velocity by its absolute value will give the sign of the value
			m_PhysicsBody->SetAngularVelocity((currentAngularVelocity / absoluteValue) * PLAYER_MAXROTATIONSPEED);

		//Check tha health
		if (m_CurrentHealth <= 0)
			KillPlayer();

	}
	else
	{
		//Tick down respawn timer
		respawnTimer -= deltaTime;
		if (respawnTimer <= 0)
		{
			Respawn();
		}
	}

	//Update GUI values
	UpdateGUI();
}

void Player::OnCollision(CollisionEvent collisionEvent)
{
	if (playerAlive)
	{
		if (collisionEvent.other->GetCollider()->GetCollisionLayer() == (unsigned int)CollisionLayer::ROCK)
		{
			//Get component of velocity that is pointing away from the normal (toward the rock)
			float impactSpeed = Vector2::Dot(m_PhysicsBody->GetVelocity(), -collisionEvent.collisionNormal);
		
			//Instakill player cos they hit the rock too hard
			if (impactSpeed > PLAYER_IMPACT_INSTAKILL)
			{
				SetHealth(0);
			}
			//Normal impact damage
			else if (impactSpeed > PLAYER_IMPACT_SPEED)
			{
				SetHealth(GetHealth() - PLAYER_IMPACT_DAMAGE);
			}
		}
	}
}

int Player::GetLives()
{
	return lives;
}

void Player::SetLives(int lives)
{
	this->lives = lives;
}

void Player::SetGUI(GUI* gui)
{
	this->gui = gui;
}

void Player::UpdateGUI()
{
	gui->SetHealth(m_CurrentHealth);
	gui->SetLives(this->lives);
}

PhysicsBody* Player::GetPhysicsBody()
{
	return m_PhysicsBody;
}

void Player::KillPlayer()
{
	playerAlive = false;
	lives--;
	//Do some fun physics stuff when it dies
	m_PhysicsBody->AddForce(-m_LocalTransform.GetRight() * PLAYER_DEATH_IMPULSE);
	m_PhysicsBody->AddAngularVelocity(PLAYER_DEATH_SPIN * DEG2RAD);
	//Start respawn timer
	respawnTimer = PLAYER_RESPAWN_TIME;
}

void Player::Respawn()
{
	playerAlive = true;
	//Reset health and physics values
	m_CurrentHealth = m_MaxHealth;
	m_PhysicsBody->SetVelocity(Vector2::ZERO());
	m_PhysicsBody->SetAngularVelocity(0.0f);
	SetRotation(0.0f);

	//Set back to spawn
	SetPosition(Vector2::ZERO()/*Spawn point to be added*/);
}