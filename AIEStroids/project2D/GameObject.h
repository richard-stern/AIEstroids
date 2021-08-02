#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Matrix3.h"
#include "Vector2.h"
#include "DynamicArray.h"


class CollisionEvent;

class GameObject
{
public:
	GameObject();
	GameObject(Vector2 _pos);
	virtual ~GameObject();

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer2D);

	GameObject* GetParent() { return m_Parent; }
	void SetParent(GameObject* _parent) { m_Parent = _parent; }

	DynamicArray<GameObject*> GetChildren() { return m_Children; }
	void SetChild(GameObject* _child) { m_Children.Add(_child); }

	Vector2 GetLocalPosition() { return m_LocalTransform.GetPosition(); }
	void SetLocalPosition(Vector2 _pos) { m_LocalTransform.SetPosition(_pos); }
	
	Vector2 GetGlobalPosition() { return m_GlobalTransform.GetPosition(); }

	Vector2 GetVelocity() { return m_Velocity; }
	void SetVelocity(Vector2 _velocity) { m_Velocity = _velocity; }

	float GetDrag() { return m_Drag; }
	void SetDrag(float _drag) { m_Drag = _drag; }

	bool GetActive() { return m_IsActive; }
	void SetActive(bool _active) { m_IsActive = _active; }

	aie::Texture* GetTexture() { return m_Texture; }
	void SetTexture(aie::Texture* _texture) { m_Texture = _texture; }

	//virtual void OnCollision(CollisionEvent _event);

protected:
	GameObject* m_Parent = nullptr;
	DynamicArray<GameObject*> m_Children;

	Matrix3 m_GlobalTransform;
	Matrix3 m_LocalTransform;

	Vector2 m_Velocity = { 0, 0 };
	float m_Drag = 0;

	aie::Texture* m_Texture;
	bool m_IsActive = false;
	bool m_WrapAndRespawn = false;
};

