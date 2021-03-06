#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "DynamicArray.h"
#include "Matrix3.h"
#include "Vector2.h"
#include "CollisionManager.h"
#include "Application.h"

// Author: James K

class GameObject
{
public:
	GameObject();
	GameObject(Vector2 _pos, GameObject* _parent = nullptr);
	virtual ~GameObject();

	virtual void Update(float _deltaTime);
	virtual void UpdateTransforms();
	virtual void Draw(aie::Renderer2D* _renderer2D);

	GameObject* GetParent() { return m_Parent; }
	void SetParent(GameObject* _parent) { m_Parent = _parent; }

	DynamicArray<GameObject*> GetChildren() { return m_Children; }
	void AddChild(GameObject* _child) { m_Children.Add(_child); }

	Matrix3 GetGlobalTransform() { return  m_GlobalTransform; }
	Matrix3 GetLocalTransform() { return  m_LocalTransform; }
	Vector2 GetGlobalPosition() { return  m_GlobalTransform.GetPosition(); }
	Vector2 GetPosition() { return  m_LocalTransform.GetPosition(); }

	void SetLocalTransform(Matrix3 _transform) { m_LocalTransform = _transform; }
	void SetPosition(Vector2 _pos) { m_LocalTransform.SetPosition(_pos); }
	float GetRotation() { return m_LocalTransform.GetRotation(); }
	void SetRotation(float _radians) { m_LocalTransform.SetRotation(_radians); }

	bool GetActive() { return m_IsActive; }
	void SetActive(bool _active) { m_IsActive = _active; }

	aie::Texture* GetTexture() { return m_Texture; }
	void SetTexture(aie::Texture* _texture) { m_Texture = _texture; }
	void SetSpriteDepth(float _depth);

	virtual void OnCollision(CollisionEvent _event);
	
protected:
	
	GameObject* m_Parent = nullptr;
	DynamicArray<GameObject*> m_Children;

	Matrix3 m_GlobalTransform;
	Matrix3 m_LocalTransform;

	Vector2 m_SpawnPoint;
	float m_Drag = 0;

	aie::Texture* m_Texture = nullptr;
	float m_SpriteDepth = 0;
	bool m_IsActive = false;
	bool m_WrapAndRespawn = false;
};

