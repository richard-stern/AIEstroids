#include "Actor.h"
#include "Application.h"
#include "PhysicsBody.h"
#include "CollisionManager.h"

#define LEVEL_SIZE 20000

Actor::Actor()
{
	SetPosition({ 0, 0 });
	SetHealth(m_MaxHealth);
	
}

Actor::Actor(Vector2 _pos, GameObject* _parent)
{
	SetPosition(_pos);
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
	
	// V2 thisPos
	// V2 cameraPos
	// int xThresh
	// int yThresh
	
	//difference.x = thispos.x - campos.x

	// if (thisPos.x < campos.x + xThresh)
	// SetPos(-, thispos.y 


	if (m_WrapAndRespawn)
	{
		//int h = application->GetWindowHeight();
		//int w = application->GetWindowWidth();
		//Vector2 pos = GetPosition();

		//// if actor moves off the screen horizontally
		//if (pos.x > w)
		//{
		//	SetPosition({ (float)-w, pos.y });
		//}
		//else if (pos.x < 0)
		//{
		//	SetPosition({ (float)w, pos.y });
		//}
		//// vertically
		//if (pos.y > h)
		//{
		//	SetPosition({ pos.x, (float)-h });
		//}
		//else if (pos.x < 0)
		//{
		//	SetPosition({ pos.x, (float)-h });
		//}
	}
}

void Actor::OnCollision(CollisionEvent _event)
{

}

void Actor::GeneratePhysicsBody(aie::Texture* texture, CollisionLayer layer, unsigned short layerMask)
{
	Shape* shape = PolygonShape::CreateBox(texture->GetWidth() / 2.0f, texture->GetHeight() / 2.0f, Vector2::ZERO());
	auto collider = new Collider(shape, (unsigned short)layer, layerMask);
	m_PhysicsBody = new PhysicsBody(this, BodyType::DYNAMIC, collider);
}

void Actor::GeneratePhysicsBody(float _width, float _height, CollisionLayer layer, unsigned short layerMask)
{
	Shape* shape = PolygonShape::CreateBox(_width / 2.0f, _height / 2.0f, Vector2::ZERO());
	auto collider = new Collider(shape, (unsigned short)layer, layerMask);
	m_PhysicsBody = new PhysicsBody(this, BodyType::DYNAMIC, collider);
}

void Actor::GenerateCircleBody(float _radius, CollisionLayer layer, unsigned short layerMask)
{
	Shape* shape = new CircleShape(Vector2::ZERO(), _radius);
	auto collider = new Collider(shape, (unsigned short)layer, layerMask);
	m_PhysicsBody = new PhysicsBody(this, BodyType::DYNAMIC, collider);
}


