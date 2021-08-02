#pragma once
#include "GameObject.h"

// Author: James K

class Actor : public GameObject
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update() override;

	bool GetWrapAndRespawn() { return m_WrapAndRespawn; }
	void SetWrapAndRespawn(bool _active) { m_WrapAndRespawn = _active; }

	PhysicsBody* GetPhysicsBody() { return m_PhysicsBody; }
	void SetPhysicsBody(PhysicsBody* _body) { m_PhysicsBody = _body; }

	virtual void OnCollision(CollisionEvent _event);

protected:
	PhysicsBody* m_PhysicsBody = nullptr;

	bool m_WrapAndRespawn = false;
};

