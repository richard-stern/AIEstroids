#pragma once
#include "Vector2.h"
#include "Renderer2D.h"
#include "Game2D.h"

class Camera
{
public:
	static void Create(aie::Renderer2D* _renderer, Player* _player);
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

	float minMoveDistance = 0.0f;
	int distancePercentPerFrame = 5; //100 is rigid-follow, 0 is no follow

	Vector2 cameraPosition;
	aie::Renderer2D* renderer;
	Player* player;
};

