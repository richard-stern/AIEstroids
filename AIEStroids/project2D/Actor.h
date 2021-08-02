#pragma once
#include "GameObject.h"

class Actor : public GameObject
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer2D);
	Matrix3 GetGlobalTransform() { return m_GlobalTransform; }
	Matrix3 GetLocalTransform() { return m_LocalTransform; }

protected:
	Vector2 m_v2Velocity;
	Vector2 m_MaxVelocity;
	int m_nHealth;
	int m_nMaxHealth;	
	
private:

	bool m_WrapAndRespawn = false;
};

