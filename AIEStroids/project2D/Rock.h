#pragma once
#include <stdlib.h>
#include <time.h>
#include "Matrix3.h"
#include "Vector2.h"
#include "Actor.h"
class Rock : public Actor
{
public:
	Rock();
	~Rock();
	void Update(float deltaTime) override;
	void OnCollision(GameObject* other);


private:
	void SetRandomPath();
};