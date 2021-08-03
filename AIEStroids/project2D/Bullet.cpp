#include "Bullet.h"
#include "TextureManager.h"

//Constructor
Bullet::Bullet() : Actor::Actor()
{
	//uses function from the TextureManager to load the texture from the bullet
	m_Texture = TextureManager::Get()->LoadTexture("../bin/sprites/Bullets_3.png");

	//Set the variable to false
	m_WrapAndRespawn = false;

	//Sets the variable float value to 10 
	m_fLifeTime = 10;

	//Sets the variable to equal the the same value as the other variable
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
	SetPosition(position);

}

//Function gets updated allowing to use deltaTime 
void Bullet::Update(float m_fDeltaTime)
{
	//If the bullet fired m_bActive is true run
	if (m_bActive)
	{
		//m_fLifeTimeTimer new values equals m_fLifeTimeTimer minus deltaTime
		m_fLifeTimeTimer -= m_fDeltaTime;

		//If m_fLifeTimeTimer value is smaller or equal to 0 run
		if (m_fLifeTimeTimer <= 0)
		{
			//Set the bullet m_bActive to false meaing the bullet is no longer renderer on screen
			m_bActive = false;
		}
	}
}

//Collision for the bullet when made contact with another object
void Bullet::OnCollision(CollisionEvent _event)
{
	m_bActive = false;
}