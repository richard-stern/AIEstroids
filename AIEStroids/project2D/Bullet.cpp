#include "Bullet.h"

//Constructor
Bullet::Bullet() : Actor::Actor()
{
	//uses function from the TextureManager to load the texture from the bullet
	m_Texture = TextureManager::Get()->LoadTexture("../bin/sprites/Bullets_3.png");

	//Set the variable to false
	m_WrapAndRespawn = false;

	//Sets the variable float value to 4
	m_fLifeTime = 4;

	//Sets the variable to equal the the same value as the other variable
	m_fLifeTimeTimer = m_fLifeTime;

	//Creates a clipping mask so the bullet and Player can't make contact with each other
	m_nActiveLayer = (unsigned int)CollisionLayer::ALL ^ ((unsigned int)CollisionLayer::PLAYER | (unsigned int)CollisionLayer::BULLET);
	GeneratePhysicsBody(32, 32, (CollisionLayer)0, m_nActiveLayer);
}

//Destructor
Bullet::~Bullet()
{
}

//Bullet fire actions
//takes in the position and angle 
void Bullet::Shoot(Vector2 position, float angle)
{
	//Conllision
	m_PhysicsBody->GetCollider()->SetCollisionLayer((unsigned int)CollisionLayer::BULLET);
	
	//Starts the timer on the bullet before deleted
	m_fLifeTimeTimer = m_fLifeTime;

	//Calls function to make visable so it will renderer
	SetActive(true);

	//Set the local position of the bullet
	SetPosition(position);

	//Set the rotation of the bullet when fired to face the way the turret faces
	SetRotation(angle);

	//speed of the bullet when fired
	m_PhysicsBody->SetVelocity(Vector2(cos(angle),sin(angle)) * 1000);
}

//Function gets updated allowing to use deltaTime 
void Bullet::Update(float m_fDeltaTime)
{
	//If the bullet fired m_bActive is true run
	if (GetActive())
	{
		//m_fLifeTimeTimer new values equals m_fLifeTimeTimer minus deltaTime
		m_fLifeTimeTimer -= m_fDeltaTime;

		//If m_fLifeTimeTimer value is smaller or equal to 0 run
		if (m_fLifeTimeTimer <= 0)
		{
			//Set the bullet m_bActive to false meaing the bullet is no longer renderer on screen
			SetActive(false);
			
			//Conllision
			m_PhysicsBody->GetCollider()->SetCollisionLayer(0);
			
			//Resets the Timer back to 4
			m_fLifeTimeTimer = m_fLifeTime;
		}
	}
}

//Collision for the bullet when made contact with another object
void Bullet::OnCollision(CollisionEvent _event)
{
	//Gets rid of the bullet when it hits an object
	SetActive(false);

	//Conllision
	m_PhysicsBody->GetCollider()->SetCollisionLayer(0);

	//Reset timer
	m_fLifeTimeTimer = m_fLifeTime;
}