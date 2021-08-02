#include "BulletManager.h"
#include "Bullet.h"
#define MAX_BULLET 30

BulletManager::BulletManager()
{
	pBullet = new Bullet * [MAX_BULLET];

	for (int i = 0; i < MAX_BULLET; ++i)
	{
		/*pBullet[i] = new Bullet();*/
		pBullet[i] = nullptr;
	}
}

BulletManager::~BulletManager()
{
	for (int i = 0; i < MAX_BULLET; ++i)
	{
		delete pBullet[i];
	}
	delete[] pBullet;
}

void BulletManager::ShootBullet()
{
	bool run = true;

	while (run)
	{
		for (int i = 0; i < MAX_BULLET; ++i)
		{
			if (pBullet[i] = nullptr)
			{
				pBullet[i] = new Bullet();

				pBullet[i]->Shoot();

				run = false;
			}
		}
	}
}
