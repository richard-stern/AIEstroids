#include "Enemy.h"
#include "Application.h"

Enemy::Enemy() : m_destroyed(false)
{
	//m_v2Velocity = ;
	//m_fDrag = ;
	//m_pCollider = ;
	//m_pTexture = ;
	//m_m3LocalMatrix = ;
	m_m3GlobalMatrix = GetRandomLocation();
	//m_pParent = ;
	//m_Children = ;
	//m_bVisible = ;
	//m_bWrapAndRespawn = ;
	m_nHealth = 100;
	m_nMaxHealth = 100;

	// initialize random seed: 
	srand(time(NULL));
	// pick random direction
	
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{

}

void Enemy::Draw()
{

}

void Enemy::OnCollision(GameObject other)
{

}

void Enemy::Seek()
{

}

Matrix3 Enemy::GetRandomLocation()
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

	return Matrix3;
}