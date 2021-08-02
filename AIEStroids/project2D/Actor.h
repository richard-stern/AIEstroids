#pragma once
#include "GameObject.h"

// Author: James K

class Actor : public GameObject
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer2D);
	Matrix3 GetGlobalTransform() { return m_GlobalTransform; }
	Matrix3 GetLocalTransform() { return m_LocalTransform; }

	bool GetWrapAndRespawn() { return m_WrapAndRespawn; }
	void SetWrapAndRespawn(bool _active) { m_WrapAndRespawn = _active; }
protected:
	Vector2 m_v2Velocity;
	Vector2 m_MaxVelocity;
	int m_nHealth;
	int m_nMaxHealth;	
	
private:

protected:
	bool m_WrapAndRespawn = false;

};

