#pragma once
#include "Vector2.h"
#include "Renderer2D.h"
#include "Game2D.h"

class Player;

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
	void Shake(float strength, float duration);
	bool IsPointOnScreen(Vector2 point);

private:
	Camera();
	~Camera();
	static Camera* instance;

	float minMoveDistance = 0.25f; //The smallest distance the camera is allowed to move in one frame
	int followSpeed = 5; //Higher numbers mean the camera has less delay

	Vector2 cameraPosition;
	aie::Renderer2D* renderer;
	Player* player;
	aie::Application* application;

	//Updated when the Shake() function is called
	float shakeStrength;
	float shakeDuration;
	float shakeTimer;
};

