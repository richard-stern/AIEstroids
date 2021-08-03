#pragma once
#include "GameObject.h"

// Author: James K

struct CollisionEvent;
class PhysicsBody;

class Actor : public GameObject
{
public:
	Actor();
	Actor(Vector2 _pos);
	virtual ~Actor();

	virtual void Update(float _deltaTime) override;

	int GetHealth() { return m_CurrentHealth; }
	void SetHealth(int _health) { m_CurrentHealth = _health; }

	bool GetWrapAndRespawn() { return m_WrapAndRespawn; }
	void SetWrapAndRespawn(bool _active) { m_WrapAndRespawn = _active; }
	Vector2 GetVelocity() { return m_Velocity; }

	virtual void OnCollision(CollisionEvent _event);
	void AddPhysicsBody(PhysicsBody* _body) { m_PhysicsBody = _body; }
	void RemovePhysicsBody() { m_PhysicsBody = nullptr; }

protected:
	PhysicsBody* m_PhysicsBody = nullptr;

	const int m_MaxHealth = 100;
	int m_CurrentHealth;
	
	bool m_WrapAndRespawn = false;
};

