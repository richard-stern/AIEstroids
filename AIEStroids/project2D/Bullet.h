//Not all of this is right just a rough idea of what i think
//so i don't forget what i tried and can work on later to fix

#pragma once
#include "Actor.h"
#include "TextureManager.h"
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
	virtual void Update(float _deltaTime) override;
	//Collision with bullets
	virtual void OnCollision(CollisionEvent _event) override;

private:
	
	aie::Texture* m_MyTexture;

	//bool for a fucntion to make visable
	bool m_bActive = true;

	//Velocity of the bullet being fired
	Vector2 m_v2Velocity;
	float m_fLifeTime;
	float m_fLifeTimeTimer;
};

