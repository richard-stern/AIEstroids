#include "BulletManager.h"
#include "Bullet.h"

//Cap it just for now will change later
#define MAX_BULLET 100

//Constructor
BulletManager::BulletManager()
{
	m_bActive = true;

	//create the bullet array 
	pBullet = new Bullet * [MAX_BULLET];
	//pBullet is true
	if (pBullet)
	{
		//for loop that ruins through the array creating the pBullets
		//for all pBullet in the array set active as false
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
	//For loop to find the pBullet closes to the start of the array tha active equals false
	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (pBullet[i]->GetActive() == false)
		{
			//Set the pBullet to true
			pBullet[i]->SetActive(true);

			//calls thje shoot function from Bullet cpp file that will
			//create a bullet from the posision from the araay
			pBullet[i]->Shoot(position, angle);

			break;
		}
	}
}
