#include "Actor.h"
#include "Application.h"
#include "PhysicsBody.h"
#include "CollisionManager.h"

Actor::Actor()
{
	m_GlobalTransform.SetPosition({ 0, 0 });
	SetHealth(m_MaxHealth);
}

Actor::Actor(Vector2 _pos)
{
	m_GlobalTransform.SetPosition(_pos);
	SetHealth(m_MaxHealth);
}

Actor::~Actor()
{
	delete m_PhysicsBody;
	m_PhysicsBody = nullptr;
}

void Actor::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);

	aie::Application* application = aie::Application::GetInstance();
	if (m_WrapAndRespawn)
	{
		int h = application->GetWindowHeight();
		int w = application->GetWindowWidth();
		Vector2 pos = GetLocalPosition();

		// if actor moves off the screen horizontally
		if (pos.x > w)
		{
			SetLocalPosition({ (float)-w, pos.y });
		}
		else if (pos.x < 0)
		{
			SetLocalPosition({ (float)w, pos.y });
		}
		// vertically
		if (pos.y > h)
		{
			SetLocalPosition({ pos.x, (float)-h });
		}
		else if (pos.x < 0)
		{
			SetLocalPosition({ pos.x, (float)-h });
		}
	}
	
}

void Actor::OnCollision(CollisionEvent _event)
{

}
