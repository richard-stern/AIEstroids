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

	GeneratePhysicsBody(200, 200, CollisionLayer::ENEMY, 0xff);

	//Assign ship texture
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/enemy_small.png");

	SetRandomLocation();

	SetRotation(M_PI / 2);
}

Enemy::Enemy(Vector2 pos, Player* player, Rock** rocks) : m_destroyed(false)
{
	SetPosition(pos);
	m_player = player;
	m_rocks = rocks;
	m_CurrentHealth = m_MaxHealth;

	GeneratePhysicsBody(200, 200, CollisionLayer::ENEMY, 0xff);

	//Assign ship texture
	m_Texture = TextureManager::Get()->LoadTexture("../bin/textures/enemy_small.png");

	SetRotation((float)(M_PI));
}

Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	Vector2 velocity = m_PhysicsBody->GetVelocity();
	Seek(m_player, deltaTime);
	CollisionAvoidance(deltaTime);

	// smooth out the steering
	if (steeringForce.GetMagnitude() > MAX_SEE_AHEAD)
	{
		steeringForce = steeringForce.GetNormalised();
		steeringForce *= MAX_SEE_AHEAD;
	}

	// update the velocity of the enemy
	m_PhysicsBody->SetVelocity(velocity + steeringForce *deltaTime);

	// rotate enemy ship
	float rotation = atan2(velocity.y, velocity.x) + M_PI / 2;

	// set random rotation
	SetRotation(rotation);

	//GetGlobalTransform().GetUp();
}

void Enemy::OnCollision(GameObject* other)
{
	if (other == m_player)
	{
		m_CurrentHealth = 0; // destroy enemy ship
		m_player->SetHealth(m_player->GetHealth() - 10); // damage the player
	}
	else
		m_CurrentHealth -= 10;
}

void Enemy::Seek(Actor* target, float deltaTime)
{
	Vector2 targetPos = target->GetPosition();
	Vector2 difference = targetPos - GetPosition();

	Vector2 desiredVelocity = difference.GetNormalised() * MAX_ENEMY_VELOCITY;
	steeringForce = desiredVelocity - m_PhysicsBody->GetVelocity();
}

void Enemy::SetRandomLocation()
{
	// initialize random seed: 
	srand((unsigned int)time(NULL));

	aie::Application* app = aie::Application::GetInstance();

	int width = app->GetWindowWidth();
	int height = app->GetWindowHeight();

	int x = rand() % 2*width + (-width);
	int y = rand() % 2*height + (-height);

	Vector2 spawnPos = { (float)x, (float)y };

	SetPosition(spawnPos);
}

void Enemy::Pursue(float deltaTime)
{
	Vector2 playerVelocity = m_player->GetPhysicsBody()->GetVelocity();

	Vector2 V = m_player->GetPosition() + playerVelocity - this->GetPosition();
	Vector2 force = V.GetNormalised() * MAX_ENEMY_VELOCITY - playerVelocity;
}

void Enemy::CollisionAvoidance(float deltaTime)
{
	Vector2 velocity = m_PhysicsBody->GetVelocity();

	// calculate the ahead and ahead2 vectors
	Vector2 ahead = GetPosition() + velocity.GetNormalised() * MAX_SEE_AHEAD; 
	Vector2 ahead2 = GetPosition() + velocity.GetNormalised() * MAX_SEE_AHEAD * 0.5f;

	GameObject* mostThreatening = FindMostThreateningObstacle(ahead, ahead2);
	Vector2 avoidance = { 0, 0 };

	if (mostThreatening != nullptr) {
		avoidance.x = ahead.x - mostThreatening->GetPosition().x;
		avoidance.y = ahead.y - mostThreatening->GetPosition().y;

		avoidance.GetNormalised();
		avoidance *= MAX_AVOID_FORCE;
	} 
	else
	{
		avoidance *= 0;  // nullify the avoidance force
	}

	steeringForce += avoidance;
}

GameObject* Enemy::FindMostThreateningObstacle(Vector2 ahead1, Vector2 ahead2)
{
	GameObject* mostThreatening = nullptr;
	Vector2 position = GetPosition();

	for (int i = 0; i < ROCKS_COUNT; i++) {
		bool collision = LineIntersectsCircle(ahead1, ahead2, m_rocks[i]);

		// "position" is the character's current position
		if (collision && (mostThreatening == nullptr ||
			position.GetDistance(m_rocks[i]->GetPosition()) <
			position.GetDistance(mostThreatening->GetPosition())))
		{
			mostThreatening = (GameObject*) m_rocks[i];
		}
	}

	return mostThreatening;
}

bool Enemy::LineIntersectsCircle(Vector2 ahead1, Vector2 ahead2, GameObject* obstacle)
{
	float ahead1Distance = obstacle->GetPosition().GetDistance(ahead1);
	float ahead2Distance = obstacle->GetPosition().GetDistance(ahead2);

	return (ahead1Distance <= ROCK_RADIUS || ahead2Distance <= ROCK_RADIUS);
}