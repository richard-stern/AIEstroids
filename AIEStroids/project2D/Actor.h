#pragma once
#include "GameObject.h"

#define MAX_HEALTH 100

// Author: James K

class Actor : public GameObject
{
public:
	Actor();
	Actor(Vector2 _pos);
	virtual ~Actor();

	virtual void Update() override;

	int GetHealth() { return m_Health; }
	void SetHealth(int _health) { m_Health = _health; }

	bool GetWrapAndRespawn() { return m_WrapAndRespawn; }
	void SetWrapAndRespawn(bool _active) { m_WrapAndRespawn = _active; }

	void AddPhysicsBody(PhysicsBody* _body) { m_PhysicsBody = _body; }
	void RemovePhysicsBody() { m_PhysicsBody = nullptr; }


	virtual void OnCollision(CollisionEvent _event);

protected:
	PhysicsBody* m_PhysicsBody = nullptr;
	
	int m_Health = 0;
	
	bool m_WrapAndRespawn = false;
};

