#pragma once
#include "GameObject.h"

// Author: James K

class Actor : public GameObject
{
public:
	Actor(Vector2 startPos);
	virtual ~Actor();

	virtual void Update();
	//virtual void OnCollision(CollisionEvent collisionEvent) override;
	virtual void Draw(aie::Renderer2D* _renderer2D);

	bool GetWrapAndRespawn() { return m_WrapAndRespawn; }
	void SetWrapAndRespawn(bool _active) { m_WrapAndRespawn = _active; }

protected:
	bool m_WrapAndRespawn = false;

};

