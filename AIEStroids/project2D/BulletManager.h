#pragma once
#include "Vector2.h"
#include "Renderer2D.h"

class Bullet;

class BulletManager
{
public:
	//Constructor
	BulletManager();

	//Destructor
	~BulletManager();

	//Selecting a bullet to be fired and pass to the Bullet.cpp Shoot function
	void ShootBullet(Vector2 position, float angle);

	//Updates the bullets
	void Update(float deltaTime);

	//Draws the bullets
	void Draw(aie::Renderer2D* _renderer2D);

private:
	//Creates a pointer to the Bullet class
	Bullet** pBullet;
};

