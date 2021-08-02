#pragma once
#include "GameObject.h"

class Actor : public GameObject
{
public:
	Actor(Vector2 startPos);
	virtual ~Actor();

	virtual void Update();
	//virtual void OnCollision(CollisionEvent collisionEvent) override;
	virtual void Draw(aie::Renderer2D* _renderer2D);

	
private:

	bool m_WrapAndRespawn = false;
};

