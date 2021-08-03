#include "Actor.h"
#include "Application.h"
#include "PhysicsBody.h"
#include "CollisionManager.h"

Actor::Actor()
{
	m_GlobalTransform.SetPosition({ 0, 0 });
	SetHealth(MAX_HEALTH);
}

Actor::Actor(Vector2 _pos)
{
	m_GlobalTransform.SetPosition(_pos);
	SetHealth(MAX_HEALTH);
}

Actor::~Actor()
{
	delete m_PhysicsBody;
	m_PhysicsBody = nullptr;
}

void Actor::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	
	/*
	int h = 0; // Screen Height
	int w = 0; // Screen Width
	Vector2 pos = GetLocalPosition();

	// if actor moves off the screen horizontally
	if (pos.x > w)
	{
		SetLocalPosition({ -w, pos.y });
	}
	else if (pos.x < 0)
	{
		SetLocalPosition({ w, pos.y });
	}
	// vertically
	if (pos.y > h)
	{
		SetLocalPosition({ pos.x, -h });
	}
	else if (pos.x < 0)
	{
		SetLocalPosition({ pos.x, -h });
	}
	*/
}

void Actor::OnCollision(CollisionEvent _event)
{

}
