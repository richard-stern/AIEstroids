#pragma once
#include "GameObject.h"

class Actor : public GameObject
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer2D);

	
private:

	bool m_WrapAndRespawn = false;
};

