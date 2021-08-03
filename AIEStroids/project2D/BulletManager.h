#pragma once
#include "Vector2.h"

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

private:
	Bullet** pBullet;

	bool m_bActive;
};

