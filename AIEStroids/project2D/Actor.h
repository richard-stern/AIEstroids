#pragma once
#include "GameObject.h"
#include "CollisionLayers.h"

// Author: James K

struct CollisionEvent;
class PhysicsBody;

class Actor : public GameObject
{
public:
	Actor();
	Actor(Vector2 _pos, GameObject* _parent = nullptr);
	virtual ~Actor();

	virtual void Update(float _deltaTime) override;

	int GetHealth() { return m_CurrentHealth; }
	void SetHealth(int _health) { m_CurrentHealth = _health; }

	bool GetWrapAndRespawn() { return m_WrapAndRespawn; }
	void SetWrapAndRespawn(bool _active) { m_WrapAndRespawn = _active; }

	virtual void OnCollision(CollisionEvent _event);
	void GeneratePhysicsBody(aie::Texture* texture, CollisionLayer layer, unsigned short layerMask);
	void GeneratePhysicsBody(float _width, float _height, CollisionLayer layer, unsigned short layerMask);
	void RemovePhysicsBody() { m_PhysicsBody = nullptr; }

protected:
	PhysicsBody* m_PhysicsBody = nullptr;

	const int m_MaxHealth = 100;
	int m_CurrentHealth;
	
	bool m_WrapAndRespawn = false;
};

