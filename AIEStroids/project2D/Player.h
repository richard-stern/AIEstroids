#pragma once
#include "Actor.h"
#include "Turret.h"

//Author Rahul J. (BEANMEISTER)

#define LIVES 3
#define PLAYER_INPUT_UP aie::INPUT_KEY_W
#define PLAYER_INPUT_DOWN aie::INPUT_KEY_S
#define PLAYER_INPUT_RIGHT aie::INPUT_KEY_D
#define PLAYER_INPUT_LEFT aie::INPUT_KEY_A

#define PLAYER_MAXSPEED 250.0f
#define PLAYER_MAXROTATIONSPEED 250.0f
#define PLAYER_THRUST 500.0f
#define PLAYER_TORQUE 750.0f
#define PLAYER_COUNTERFORCE_MULT 2.5f
#define PLAYER_COUNTERTORQUE_MULT 2.5f
#define PLAYER_ROTATIONAL_DRAG 3.5f
#define PLAYER_DRAG 0.8f

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
	Turret* turret = nullptr;
	GUI* gui = nullptr;
};

