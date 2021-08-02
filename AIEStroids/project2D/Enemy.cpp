#include "Enemy.h"
#include "Application.h"
#include "GameObject.h"

Enemy::Enemy() : m_destroyed(false)
{
	m_v2Velocity = { 0, 0 };
	//m_fDrag = ;
	//m_pCollider = ;
	//m_pTexture = ;
	m_m3LocalMatrix.ResetToIdenity();
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
	m_player->m_GlobalTransform[0] = position.x;
	m_player->m_GlobalTransform[4] = position.y;

	Seek(deltaTime);
}

void Enemy::Draw(aie::Renderer2D* renderer)
{
	renderer->DrawBox(position.x, position.y, 32, 48, 0, 1);
}

void Enemy::OnCollision(GameObject* other)
{

	m_destroyed = true;
}

void Enemy::Seek(float deltaTime)
{
	m_position = { m_GlobalTransform[0], m_GlobalTransform[4] };
	Vector2 playerPos = m_player->m_GlobalTransform[0], m_player->m_GlobalTransform[4];

	Vector2 difference = playerPos - enemyPos;

	float desiredVelocity = difference.get_normalised() * m_MaxVelocity;
	float steeringForce = desiredVelocity - m_v2Velocity;
	
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