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
	
	int h = 0; // Screen Height
	int w = 0; // Screen Width
	Vector2 pos = GetLocalPosition();

}

// TODO
float Actor::WrapAndRespawn(float _coordinate, float _max)
{
	//_coordinate %= _max + 1;
	//if (_coordinate < 0)
	//{
	//	_coordinate += _max;
	//}
	//return _coordinate;
}

void Actor::OnCollision(CollisionEvent _event)
{

}
