#include "Player.h"
#include "Application.h"
#include "GUI.h"
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
	Vector2 currentVelocity = m_PhysicsBody->GetVelocity();

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

	float thrustAmount = PLAYER_THRUST;
	m_PhysicsBody->AddVelocity(m_GlobalTransform.GetRight() * inputVector.y * PLAYER_THRUST * deltaTime);
	m_PhysicsBody->AddAngularVelocity(inputVector.x * PLAYER_TORQUE * deltaTime);
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
	//
}

PhysicsBody* Player::GetPhysicsBody()
{
	return m_PhysicsBody;
}
