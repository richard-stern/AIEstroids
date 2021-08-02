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

	//m_player = level->GetPlayer();

	// pick random direction
	SetRandomLocation();
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	m_position = GetGlobalPosition();

	//SetTransform(globalTranform);

	Seek(deltaTime);
}

void Enemy::Draw(aie::Renderer2D* renderer)
{
	//renderer->DrawBox(GetGlobalPosition().x, GetGlobalPosition().y, 32, 48, 0, 1);
	renderer->DrawBox(m_position.x, m_position.y, 32, 48, GetRotation(), 1);
}

void Enemy::OnCollision(GameObject* other)
{

	m_destroyed = true;
}

void Enemy::Seek(float deltaTime)
{
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
	// initialize random seed: 
	srand(time(NULL));

	aie::Application* app = aie::Application::GetInstance();

	int x = rand() % app->GetWindowWidth();
	int y = rand() % app->GetWindowHeight();

	m_position = { (float)x, (float)y };

	SetGlobalPosition({ (float)x, (float)y });

	float rotation = rand() / 10000.0;

	// set random rotation
	SetRotationZ(rotation);
}

void Enemy::Pursue(float deltaTime)
{
	Vector2 V = m_player->GetGlobalPosition() + m_player->GetVelocity() - this->GetGlobalPosition();
	Vector2 force = V.GetNormalised() * m_MaxVelocity - m_player->GetVelocity();
}

void Enemy::AvoidObstacles(float deltaTime)
{
	Vector2 newPos = GetPosition() + CollisionAvoidance() * deltaTime;

	SetGlobalPosition(newPos);
}

Vector2 Enemy::CollisionAvoidance()
{
	// calculate the ahead and ahead2 vectora
	Vector2 ahead = GetGlobalPosition() + m_v2Velocity.GetNormalised() * MAX_SEE_AHEAD; 
	Vector2 ahead2 = GetGlobalPosition() + m_v2Velocity.GetNormalised() * MAX_SEE_AHEAD * 0.5f;

	GameObject* mostThreatening = FindMostThreateningObstacle();
	Vector2 avoidance = { 0, 0 };

	if (mostThreatening != nullptr) {
		avoidance.x = ahead.x - mostThreatening->GetGlobalPosition().x;
		avoidance.y = ahead.y - mostThreatening->GetGlobalPosition().y;

		avoidance.GetNormalised();
		avoidance.Scale(avoidance, { MAX_AVOID_FORCE, MAX_AVOID_FORCE });
	} 
	else
	{
		avoidance.Scale(avoidance, { 0, 0 }); // nullify the avoidance force
	}

	return avoidance;
}

GameObject* Enemy::FindMostThreateningObstacle()
{
	GameObject* mostThreatening = nullptr;
	Vector2 position = GetPosition();

	for (GameObject* obstacle : level.GetGameObjects()) {
		bool collision;// = lineIntersectsCircle(ahead, ahead2, obstacle);

		// "position" is the character's current position
		if ((collision && mostThreatening == nullptr) ||
			position.GetDistance(obstacle->GetGlobalPosition()) < 
			position.GetDistance(mostThreatening->GetGlobalPosition()))
		{
			mostThreatening = obstacle;
		}
	}

	return mostThreatening;
}