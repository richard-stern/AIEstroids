#include "Actor.h"
#include "Application.h"

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
	GameObject::Update(float _deltaTime);
}

void Actor::OnCollision(CollisionEvent _event)
{

}
