#pragma once
#include "Actor.h"

//Author Rahul J. (BEANMEISTER)

#define LIVES 3
#define PLAYER_INPUT_UP aie::INPUT_KEY_W
#define PLAYER_INPUT_DOWN aie::INPUT_KEY_S
#define PLAYER_INPUT_RIGHT aie::INPUT_KEY_D
#define PLAYER_INPUT_LEFT aie::INPUT_KEY_A

#define PLAYER_MAXSPEED 250.0f
#define PLAYER_MAXROTATIONSPEED 90.0f
#define PLAYER_THRUST 100.0f
#define PLAYER_TORQUE 100.0f
#define PLAYER_COUNTERFORCE_MULT 2.5f
#define PLAYER_COUNTERTORQUE_MULT 1.5f

#define PLAYER_MAX_HEALTH 100

#define PLAYER_IMPACT_SPEED 250.0f
#define PLAYER_IMPACT_INSTAKILL 500.0f
#define PLAYER_IMPACT_DAMAGE 25

#define PLAYER_DEATH_IMPULSE 300.0f
#define PLAYER_DEATH_SPIN 45.0f
#define PLAYER_RESPAWN_TIME 3.0f

class GUI;

class Player :
	public Actor
{
public:
	Player(Vector2 startPos);
	~Player();

	void Update(float deltaTime) override;
	void OnCollision(CollisionEvent collisionEvent) override;

	int GetLives();
	void SetLives(int lives);

	void SetGUI(GUI* gui);

	void UpdateGUI();

	PhysicsBody* GetPhysicsBody();

protected:
	void KillPlayer();
	void Respawn();
	bool playerAlive = true;
	float respawnTimer = 0;
	int lives = LIVES;
	GUI* gui = nullptr;
};

