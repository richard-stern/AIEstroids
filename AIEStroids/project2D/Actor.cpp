#include "Actor.h"
#include "Application.h"
#include "PhysicsBody.h"
#include "CollisionManager.h"
#include "Camera.h"
#include <iostream>

Actor::Actor() : Actor::Actor(Vector2()) {}

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

	Vector2 cameraPos = Camera::GetInstance()->GetPosition();
	Vector2 position = GetPosition();
	aie::Application* app = app->GetInstance();
	int xThresh = 500;
	int yThresh = 500;
	int height = app->GetWindowHeight();
	int width = app->GetWindowWidth();

	
	if (m_WrapAndRespawn)
	{
		if (position.x < m_CameraPos.x - xThresh)
		{
			SetPosition({ m_CameraPos.x + width + xThresh, position.y});
			std::cout << "wrapping left to right" << std::endl;
		}
		if (position.x > m_CameraPos.x + width + xThresh)
		{
			SetPosition({ m_CameraPos.x - xThresh, position.y});
			std::cout << "wrapping right to left" << std::endl;
		}
		if (position.y < m_CameraPos.y - yThresh)
		{
			SetPosition({ position.x, m_CameraPos.y + height + yThresh});
			std::cout << "wrapping bottom to top" << std::endl;
		}
		if (position.y > m_CameraPos.y + height + yThresh)
		{
			SetPosition({ position.x, m_CameraPos.y - yThresh });
			std::cout << "wrapping top to bottom" << std::endl;
		}


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


