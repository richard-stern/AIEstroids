#pragma once
#include "Actor.h"

class GUI;

class Player :
	public Actor
{
public:
	Player();
	~Player();

	void Update() override;
	//void OnCollision(CollisionEvent collisionEvent) override;

	int GetLives();
	void SetLives(int lives);

protected:
	int lives;
	GUI* gui;
};