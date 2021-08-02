#pragma once
#include "Vector2.h"

class Camera
{
public:
	static void Create();
	static void Destroy();
	static Camera* GetInstance();

	void SetPosition(Vector2 position);
	void SetPosition(float x, float y);
	Vector2 GetPosition();

	void Update(float deltaTime);

private:
	Camera();
	~Camera();
	static Camera* instance;

	Vector2 position;
};

