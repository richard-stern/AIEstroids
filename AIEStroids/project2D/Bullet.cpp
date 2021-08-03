//Not all of this is right just a rough idea of what i think
//so i don't forget what i tried and can work on later to fix

#include "Bullet.h"

//Constructor
Bullet::Bullet() : Actor::Actor()
{
	//Get the texture for the bullet

	m_MyTexture = TextureManager::Get()->LoadTexture("");

	//Set the variable to false cause why not
	m_WrapAndRespawn = false;
	m_fLifeTime = 10;
	m_fLifeTimeTimer = m_fLifeTime;
}

//Destructor
Bullet::~Bullet()
{
}

//Bullet fire actions
//takes in the position and angle 
void Bullet::Shoot(Vector2 position, float angle)
{
	//Reset Timer
	m_fLifeTimeTimer = m_fLifeTime;

	//Calls function to make visable so it will renderer
	SetActive(m_bActive);
	
	//Basic velocity of the bullet
	m_v2Velocity = { 0, -200 };

	//Set the rotation of the bullet when fired to face the way the turret faces
	position.SetRotation(angle);

	//Set the local position of the bullet
	SetLocalPosition(position);

	//Need for the bullet to vanish either after going off the screen or after some time
	//So there will need to be some work on how to turn the bullet back to null after it vanishes
	//Gonna go with time for the bullet

}

void Bullet::Update(float _deltaTime)
{
	//Life Timer
	if (m_bActive)
	{
		m_fLifeTimeTimer -= _deltaTime;
		if (m_fLifeTimeTimer <= 0)
		{
			
			m_bActive = false;
		}
	}
}

void Bullet::OnCollision(CollisionEvent _event)
{
	m_bActive = false;
}


