/*
 * Author: Paul King
*/

#include "Enemy.h"
#include "Player.h"
#include "Application.h"
#include "Level.h"
#include "Rock.h"

Enemy::Enemy(Player* player, Rock** rocks) : m_destroyed(false)
{
	m_player = player;
	m_rocks = rocks;
	m_CurrentHealth = m_MaxHealth;

	//GeneratePhysicsBody(m_Texture, CollisionLayer::ENEMY, 0xff);
	GeneratePhysicsBody(200, 200, CollisionLayer::ENEMY, 0xff);

	SetRandomLocation();
}

Enemy::Enemy(Vector2 pos, Player* player, Rock** rocks) : m_destroyed(false), Actor(pos)
{
	SetLocalPosition(pos);
	m_player = player;
	m_rocks = rocks;
	m_CurrentHealth = m_MaxHealth;

	//GeneratePhysicsBody(m_Texture, CollisionLayer::ENEMY, 0xff);
	GeneratePhysicsBody(200, 200, CollisionLayer::ENEMY, 0xff);

}

Enemy::~Enemy()
{
	delete m_PhysicsBody;
}

void Enemy::Update(float deltaTime)
{
	Seek(deltaTime);
	//CollisionAvoidance(deltaTime);
}

void Enemy::Draw(aie::Renderer2D* renderer)
{
	Vector2 position = GetLocalPosition();

	renderer->DrawBox(position.x, position.y, 32, 48, GetRotation(), 1);
}

void Enemy::OnCollision(GameObject* other)
{
	m_Health -= 10;
}

void Enemy::Seek(float deltaTime)
{
	Vector2 playerPos = m_player->GetLocalPosition();

	Vector2 difference = playerPos - GetLocalPosition();

	Vector2 desiredVelocity = difference.GetNormalised() * MAX_ENEMY_VELOCITY;
	Vector2 steeringForce = desiredVelocity - m_PhysicsBody->GetVelocity();
	
	// update the position of the enemy
	m_PhysicsBody->SetVelocity(m_PhysicsBody->GetVelocity() + steeringForce * deltaTime);
	SetLocalPosition(playerPos + m_PhysicsBody->GetVelocity() * deltaTime);
}

void Enemy::SetRandomLocation()
{
	// initialize random seed: 
	srand((unsigned int)time(NULL));

	aie::Application* app = aie::Application::GetInstance();

	int x = rand() % app->GetWindowWidth();
	int y = rand() % app->GetWindowHeight();

	SetLocalPosition({ (float)x, (float)y });

	float rotation = (float) (rand() / 10000.0);

	// set random rotation
	SetRotation(rotation);
}

void Enemy::Pursue(float deltaTime)
{
	Vector2 playerVelocity = m_player->GetPhysicsBody()->GetVelocity();

	Vector2 V = m_player->GetLocalPosition() + playerVelocity - this->GetLocalPosition();
	Vector2 force = V.GetNormalised() * MAX_ENEMY_VELOCITY - playerVelocity;
}

void Enemy::CollisionAvoidance(float deltaTime)
{
	Vector2 velocity = m_PhysicsBody->GetVelocity();

	// calculate the ahead and ahead2 vectors
	Vector2 ahead = GetLocalPosition() + velocity.GetNormalised() * MAX_SEE_AHEAD; 
	Vector2 ahead2 = GetLocalPosition() + velocity.GetNormalised() * MAX_SEE_AHEAD * 0.5f;

	GameObject* mostThreatening = FindMostThreateningObstacle(ahead, ahead2);
	Vector2 avoidance = { 0, 0 };

	if (mostThreatening != nullptr) {
		avoidance.x = ahead.x - mostThreatening->GetLocalPosition().x;
		avoidance.y = ahead.y - mostThreatening->GetLocalPosition().y;

		avoidance.GetNormalised();
		avoidance.Scale(avoidance, { MAX_AVOID_FORCE, MAX_AVOID_FORCE });
	} 
	else
	{
		avoidance.Scale(avoidance, { 0, 0 }); // nullify the avoidance force
	}

	// update the position of the enemy
	SetLocalPosition((GetLocalPosition() + avoidance) * deltaTime);

}

GameObject* Enemy::FindMostThreateningObstacle(Vector2 ahead1, Vector2 ahead2)
{
	GameObject* mostThreatening = nullptr;
	Vector2 position = GetLocalPosition();

	for (int i = 0; i < ROCKS_COUNT; i++) {
		bool collision = LineIntersectsCircle(ahead1, ahead2, m_rocks[i]);

		// "position" is the character's current position
		if ((collision && mostThreatening == nullptr) ||
			position.GetDistance(m_rocks[i]->GetLocalPosition()) <
			position.GetDistance(mostThreatening->GetLocalPosition()))
		{
			mostThreatening = (GameObject*) m_rocks[i];
		}
	}

	return mostThreatening;
}

bool Enemy::LineIntersectsCircle(Vector2 ahead1, Vector2 ahead2, GameObject* obstacle)
{
	float ahead1Distance = obstacle->GetLocalPosition().GetDistance(ahead1);
	float ahead2Distance = obstacle->GetLocalPosition().GetDistance(ahead2);

	return (ahead1Distance <= radius || ahead2Distance <= radius);
}