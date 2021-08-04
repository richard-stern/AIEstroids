#include "BulletManager.h"
#include "Bullet.h"

//Size of how many bullets 
#define MAX_BULLET 200

//Constructor
BulletManager::BulletManager()
{
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
			//calls thje shoot function from Bullet cpp file that will
			//create a bullet from the posision from the araay
			pBullet[i]->Shoot(position, angle);

			//Exits the loop
			break;
		}
	}
}

//Updates on the Bullet
void BulletManager::Update(float deltaTime)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		if (pBullet[i]->GetActive() == true)
		{
			//Updates the Bullets GlobalPosition
			pBullet[i]->UpdateTransforms();

			//Passes in the deltaTime to the Bullet Update function to be used on bullet lifetime
			pBullet[i]->Update(deltaTime);
		}
	}
}

//Draws the bullets
void BulletManager::Draw(aie::Renderer2D* _renderer2D)
{
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//If bullet is active Draw the bullet in the array
		//if (pBullet[i]->GetActive())
			pBullet[i]->Draw(_renderer2D);
	}
}
