//Not all of this is right just a rough idea of what i think
//so i don't forget what i tried and can work on later to fix

#pragma once
#include "Actor.h"
#include <Texture.h>
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

	//Collision with bullets
	void OnCollision(/*overload*/);

private:
	aie::Texture* m_pTexture;

	//bool for a fucntion to make visable
	bool m_bActive = true;

	//Velocity of the bullet being fired
	Vector2 m_v2Velocity;
};

