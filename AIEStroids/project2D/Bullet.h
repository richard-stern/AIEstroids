#pragma once
#include "Actor.h"
//#include "TextureManager.h"
#include "Matrix3.h"
#include "Vector2.h"

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
	//aie::Texture* m_MyTexture;

	//bool for a fucntion to make visable
	bool m_bActive = true;

	//Velocity of the bullet being fired
	Vector2 m_v2Velocity;

	//Float useds for the Update function for the timer
	float m_fLifeTime;
	float m_fLifeTimeTimer;
};