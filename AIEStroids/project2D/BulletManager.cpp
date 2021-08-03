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

	pBullet = new Bullet*[MAX_BULLET];

	m_bActive = false;
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
	////bool for while loop
	//bool run = true;

	//while (run)
	//{
	//	//Runs thorugh the array to find a pBullet that is null
	//	for (int i = 0; i < MAX_BULLET; ++i)
	//	{
	//		if (pBullet[i] == nullptr)
	//		{
	//			//Creates the pBullet
	//			pBullet[i] = new Bullet();

	//			//Calls the function from Bullet.cpp
	//			pBullet[i]->Shoot(position, angle);

	//			//Sets bool to false to end while loop
	//			run = false;
	//		}
	//	}
	//}

	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (pBullet[i]->GetActive() == false)
		{
			pBullet[i]->SetActive(true);

			pBullet[i]->Shoot(position, angle);
			
			/*pBullet[i]->SetActive(false);*/
		}
	}
}
