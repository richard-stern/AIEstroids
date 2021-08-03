//Not all of this is right just a rough idea of what i think
//so i don't forget what i tried and can work on later to fix

#include "BulletManager.h"
#include "Bullet.h"

//Cap it just for now will change later
#define MAX_BULLET 30

//Constructor
BulletManager::BulletManager()
{
	////Initialise the pBullet 
	//pBullet = new Bullet * [MAX_BULLET];

	////Set all pBullet in the list to null
	//for (int i = 0; i < MAX_BULLET; ++i)
	//{
	//	pBullet[i] = nullptr;
	//}

	pBullet = new Bullet * [MAX_BULLET];
	if (pBullet)
	{
		for (int i = 0; i < MAX_BULLET; ++i)
		{
			(pBullet)[i] = new Bullet();

			if (pBullet[i])
				pBullet[i]->SetActive(false);
		}
	}
}

//Destuctor
BulletManager::~BulletManager()
{
	//Deletes the array of pBullet
	for (int i = 0; i < MAX_BULLET; ++i)
	{
		delete pBullet[i];
	}
	delete[] pBullet;
}


//Shoot Bullet function that will pass the position and angle to Bullet.cpp Shoot function
void BulletManager::ShootBullet(Vector2 position, float angle)
{

	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (pBullet[i]->GetActive() == false)
		{
			pBullet[i]->SetActive(true);

			pBullet[i]->Shoot(position, angle);

			break;
		}
	}
}
