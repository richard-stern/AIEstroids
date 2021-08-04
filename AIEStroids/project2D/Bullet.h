#pragma once
#include "Actor.h"
#include "TextureManager.h"

class Bullet : public Actor
{
public:
	//Constructor
	Bullet();

	//Destructor
	~Bullet();

	//Bullets fire 
	void Shoot(Vector2 position, float angle);

	//Update
	virtual void Update(float m_fDeltaTime) override;

	//Collision with bullets
	virtual void OnCollision(CollisionEvent _event) override;

private:
	//Float useds for the Update function for the timer
	float m_fLifeTime;
	float m_fLifeTimeTimer;

	//
	unsigned int m_nActiveLayer;
};