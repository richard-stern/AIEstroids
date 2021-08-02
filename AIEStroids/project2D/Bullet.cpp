//Not all of this is right just a rough idea of what i think
//so i don't forget what i tried and can work on later to fix

#include "Bullet.h"

//Constructor
Bullet::Bullet()
{
	//Do'n't really know how to do the texture calling but can do 
	//m_pTexture = TextureManager->LoadTexture("");

	//Can't seem to understand why i can't set it
	//m_bWrapAndRespawn = false;
}

//Destructor
Bullet::~Bullet()
{
}

//Bullet fire actions
//takes in the position and angle 
void Bullet::Shoot(Vector2 position, float angle)
{
	//Calls function to make visable so it will renderer
	SetActive(m_bActive);
	
	//Basic velocity of the bullet
	m_v2Velocity = { 0, -200 };

	//Sets the Velocity of the bullet
	SetVelocity(m_v2Velocity);

	//Set the rotation of the bullet when fired to face the way the turret faces
	position.SetRotation(angle);

	//Set the local position of the bullet
	SetLocalPosition(position);

	//Need for the bullet to vanish either after going off the screen or after some time
	//So there will need to be some work on how to turn the bullet back to null after it vanishes
}

//Collision with the bullet and other objects
void Bullet::OnCollision()
{

}
