#include "GameObject.h"

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
	//delete m_Texture;
	m_Texture = nullptr;
}

void GameObject::Update()
{

}

void GameObject::Draw(aie::Renderer2D* _renderer2D)
{

}

