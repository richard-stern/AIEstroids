#pragma once
#include "Vector2.h"
#include "Renderer2D.h"

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
	static aie::Renderer2D* renderer;

private:
	Camera();
	~Camera();
	static Camera* instance;

	float minMoveDistance = 0.0f;
	int distancePercentPerFrame = 5; //100 is rigid-follow, 0 is no follow

	Vector2 cameraPosition;
};

