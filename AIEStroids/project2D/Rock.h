#pragma once
#include <stdlib.h>
#include <time.h>
#include "Matrix3.h"
#include "Vector2.h"
#include "Actor.h"
#include "Player.h"
class Rock : public Actor
{
public:
	Rock(Player* player);
	~Rock();
	void Update(float deltaTime) override;
	void OnCollision(GameObject* other);
	

private:
	void SetRandomPath();
	Player* _player;
};