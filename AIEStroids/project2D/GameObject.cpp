#include "GameObject.h"
#include "PhysicsBody.h"


GameObject::GameObject()
{
	SetActive(true);
	m_GlobalTransform.SetPosition({ 0, 0 });
}

GameObject::GameObject(Vector2 _pos)
{
	SetActive(true);
	m_GlobalTransform.SetPosition(_pos);
}

GameObject::~GameObject()
{
	delete m_Texture;
	m_Texture = nullptr;
}

void GameObject::Update(float _deltaTime)
{
	
}

void GameObject::Draw(aie::Renderer2D* _renderer2D)
{
	if (m_IsActive)
	{
		_renderer2D->DrawSprite(m_Texture, GetLocalPosition().x, GetLocalPosition().y, 0, 0, GetRotation());
	}
}

void GameObject::OnCollision(CollisionEvent _event)
{
	// TODO
}

