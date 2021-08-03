#include "Camera.h"
#include "Renderer2D.h"
#include <cmath>
#include <iostream>

//Singleton initialisation
Camera* Camera::instance = nullptr;

//Singleton creation
void Camera::Create(aie::Renderer2D* _renderer, Player* _player)
{
	//"There can be only one!"
	if (instance == nullptr)
	{
		instance = new Camera();

		instance->renderer = _renderer;
		instance->player = _player;
	}
}

//Singleton deletion
void Camera::Destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//Gets an instance to the camera
Camera* Camera::GetInstance()
{
	//Return the instance
	return instance;
}

//Set camera postion using a vector
void Camera::SetPosition(Vector2 position)
{
	this->cameraPosition.x = position.x;
	this->cameraPosition.y = position.y;
}

//Set camera postion using 2 floats
void Camera::SetPosition(float x, float y)
{
	cameraPosition.x = x;
	cameraPosition.y = y;
}

//Returns the Vector2 position of the camera
Vector2 Camera::GetPosition()
{
	return cameraPosition;
}

void Camera::Update(float deltaTime)
{
	//Get the player's position
	Vector2 playerPosition;
	playerPosition = player->GetGlobalPosition();
	playerPosition.x *= -1;
	playerPosition.y *= -1;

	//Find the distance between the camera and the player
	Vector2 distance = (playerPosition - cameraPosition);

	//If the distance is significant enough to warrant moving the camera
	if (abs(distance.GetMagnitude()) * (followSpeed / 100.0f) * deltaTime > minMoveDistance)
	{
		//Move the camera toward the player by the distance fraction
		cameraPosition += (distance * (followSpeed / 100.0f) * deltaTime);
	}

	//Apply the member Vector2 to the renderer's camera
	renderer->SetCameraPos(cameraPosition.x, cameraPosition.y);
}

//Private constructor
Camera::Camera()
{
	//Starting position of camera
	cameraPosition.x = 0.0f;
	cameraPosition.y = 0.0f;

	//The minimum absolute distance moved by the camera while smoothing, anything less is cut off and the camera doesn't move
	minMoveDistance = 0.25f;

	//How far the camera moves towards its target per second (based on a percentage of the distance between them)
	followSpeed = 200;

	renderer = nullptr;
	player = nullptr;
}

//Private destructor
Camera::~Camera()
{
	//Not required
}
