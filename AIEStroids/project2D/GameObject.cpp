#include "GameObject.h"
#include "PhysicsBody.h"


GameObject::GameObject() : GameObject::GameObject(Vector2()) {}

GameObject::GameObject(Vector2 _pos, GameObject* _parent)
{
	SetActive(true);
	m_LocalTransform.SetPosition(_pos);

	if (m_Parent != nullptr)
	{
		SetParent(_parent);
		m_Parent->AddChild(this);
	}

	m_SpawnPoint = _pos;
}

GameObject::~GameObject()
{
	m_Parent = nullptr;
}

void GameObject::Update(float _deltaTime)
{
	//loop through all child objects and update
	for (int i = 0; i < m_Children.Count(); i++)
		m_Children[i]->Update(_deltaTime);
}

void GameObject::UpdateTransforms()
{
	if (!m_IsActive)
		return;

	// parent object's global position multiplied by the offset of the child object gives us the childs global position
	//if there's no parent, this object's local position is it's global position
	if(m_Parent != nullptr)
		m_GlobalTransform = m_Parent->m_GlobalTransform * m_LocalTransform;
	else
		m_GlobalTransform = m_LocalTransform;

	//loop through all child objects and update their transforms
	for (int i = 0; i < m_Children.Count(); i++)
		m_Children[i]->UpdateTransforms();

}

void GameObject::Draw(aie::Renderer2D* _renderer2D)
{
	//loop through all child objects and draw
	for (int i = 0; i < m_Children.Count(); i++)
		m_Children[i]->Draw(_renderer2D);

	if (m_IsActive)
	{
		_renderer2D->DrawSpriteTransformed3x3(m_Texture, m_GlobalTransform.m, 0.0f, 0.0f, m_SpriteDepth);
	}
}

void GameObject::SetSpriteDepth(float _depth)
{
	m_SpriteDepth = _depth;
}

void GameObject::OnCollision(CollisionEvent _event)
{
	// TODO
}

