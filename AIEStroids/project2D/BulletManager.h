#pragma once

class Bullet;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void ShootBullet();

private:
	Bullet** pBullet;
};

