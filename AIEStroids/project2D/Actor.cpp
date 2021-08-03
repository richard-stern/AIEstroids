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

/*
//Create a box that is the same dimensions as the texture
Shape* shape = PolygonShape::CreateBox(m_Texture->GetWidth() / 2.0f, m_Texture->GetHeight() / 2.0f, Vector2::ZERO());
//Collide with everything but player
unsigned int layermask = (unsigned int)CollisionLayer::ALL ^ (unsigned int)CollisionLayer::PLAYER;
//Create collider
Collider* collider = new Collider(shape, (unsigned short)CollisionLayer::PLAYER, layermask);
//Create the physics body using the generated collider
AddPhysicsBody(new PhysicsBody(this, BodyType::DYNAMIC, collider));
*/

//{ m_PhysicsBody = _body; }

void Actor::OnCollision(CollisionEvent _event)
{

}
