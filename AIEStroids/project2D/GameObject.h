#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Matrix3.h"
#include "Vector2.h"

class CollisionEvent;

class GameObject
{
public:
	GameObject();
	GameObject(float _posX, float _posY);
	virtual ~GameObject();

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer2D);

	Vector2 GetPosition() { return m_Position; }
	void SetPosition(Vector2 _pos) { m_Position = _pos; }


	//virtual void OnCollision(CollisionEvent _event);


private:
	Matrix3 m_GlobalTransform;
	Vector2 m_Position;
	aie::Texture* m_Texture;
	bool m_IsActive;
};

