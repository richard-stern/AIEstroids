#include "Player.h"
#include "Application.h"
#include "GUI.h"
#include <cmath>
#include "TextureManager.h"

//Author Rahul J. (BEANMEISTER)

Player::Player(Vector2 startPos) : Actor::Actor(startPos)
{
	m_WrapAndRespawn = false;
	AddPhysicsBody(new PhysicsBody(this, BodyType::DYNAMIC));
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/ship.png");
	SetLocalPosition(Vector2::ONE() * 100.0f);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
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


	//Update GUI values
	UpdateGUI();
}

void Player::OnCollision(CollisionEvent collisionEvent)
{
	m_PhysicsBody->GetVelocity();
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
