#include "Actor.h"
#include "Application.h"
#include "PhysicsBody.h"
#include "CollisionManager.h"
#include "Camera.h"

#define LEVEL_SIZE 20000

Actor::Actor(Vector2 _pos, GameObject* _parent) : GameObject::GameObject(_pos, _parent)
{
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

	m_Camera = Camera::GetInstance();
	
	if (m_WrapAndRespawn)
	{
		// V2 pos
		// V2 cameraPos
		// int xThresh
		// int yThresh

		// if (pos.x < campos.x + xThresh)
		// SetPos(campos.x + xthresh, thispos.y + rand() % ythresh)
		// if (pos.x > campos.x + xThresh)
		// SetPos(campos.x - xthresh, thispos.y + rand() % ythresh)
		// if (pos.y < campos.y + yThresh)
		// SetPos(campos.y + xthresh, thispos.y + rand() % xthresh)
		// if (pos.y > campos.y + yThresh)
		// SetPos(campos.y + xthresh, thispos.y + rand() % xthresh)

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


