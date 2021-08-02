#include "Enemy.h"
#include "Player.h"
#include "Application.h"

Enemy::Enemy() : m_destroyed(false), Actor()
{
	m_v2Velocity = { 0, 0 };
	m_Drag = 1.0f;
	//m_pCollider = ;
	//m_pTexture = ;
	m_LocalTransform.ResetToIdentity();
	//m_pParent = ;
	//m_Children = ;
	//m_bVisible = ;
	//m_bWrapAndRespawn = ;
	m_nHealth = 100;
	m_nMaxHealth = 100;

	SetRandomLocation();

	// initialize random seed: 
	srand(time(NULL));
	// pick random direction
	
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	Matrix3 globalTranform = GetGlobalTransform();

	globalTranform.m[0] = m_position.x;
	globalTranform.m[4] = m_position.y;

	//SetTransform(globalTranform);

	Seek(deltaTime);
}

void Enemy::Draw(aie::Renderer2D* renderer)
{
	renderer->DrawBox(m_position.x, m_position.y, 32, 48, 0, 1);
}

void Enemy::OnCollision(GameObject* other)
{

	m_destroyed = true;
}

void Enemy::Seek(float deltaTime)
{
	m_position = { m_GlobalTransform.m[0], m_GlobalTransform.m[4] };

	Vector2 playerPos = m_player->GetGlobalPosition();

	Vector2 difference = playerPos - m_position;

	Vector2 desiredVelocity = difference.GetNormalised() * m_MaxVelocity;
	Vector2 steeringForce = desiredVelocity - m_v2Velocity;
	
	// update the position of the enemy
	m_v2Velocity += steeringForce * deltaTime;
	m_position += m_v2Velocity * deltaTime;
}

void Enemy::SetRandomLocation()
{
	aie::Application* app = aie::Application::GetInstance();

	int x = rand() % app->GetWindowWidth();
	int y = rand() % app->GetWindowHeight();

	Matrix3 globalMatrix;
	globalMatrix.m[0] = x;
	globalMatrix.m[1] = 0;
	globalMatrix.m[2] = 0;
	globalMatrix.m[3] = 0;
	globalMatrix.m[4] = y;
	globalMatrix.m[5] = 0;
	globalMatrix.m[6] = 0;
	globalMatrix.m[7] = 0;
	globalMatrix.m[8] = 1;
}