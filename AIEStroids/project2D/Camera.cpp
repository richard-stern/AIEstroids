#include "Camera.h"
#include "Renderer2D.h"
#include <cmath>

//Singleton initialisation
Camera* Camera::instance = nullptr;

//Singleton creation
void Camera::Create()
{
	//"There can be only one!" - 429 year old singleton
	if (instance == nullptr)
	{
		instance = new Camera();
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
	//If there is no instance yet, make one. (Create() checks if there is an instance already)
	Create();

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
	//playerPosition = player->GetPosition();

	//Find the distance between the camera and the player
	Vector2 distance = playerPosition - cameraPosition;

	//If the distance is significant enough to warrant moving the camera
	if (abs(distance.GetMagnitude()) * distancePercentPerFrame * deltaTime > minMoveDistance)
	{
		//Move the camera toward the player by the distance fraction
		cameraPosition += (distance * distancePercentPerFrame * deltaTime);
	}

	//Apply the member Vector2 to the renderer's camera
	//renderer->SetCameraPos(cameraPosition.x, cameraPosition.y);
}

//Private constructor
Camera::Camera()
{
	//Starting position of camera
	cameraPosition.x = 0.0f;
	cameraPosition.y = 0.0f;

	//The minimum absolute distance moved by the camera while smoothing, anything less is cut off and the camera doesn't move
	minMoveDistance = 0.0f;

	//How far the camera moves towards its target in this frame (based on a percentage of the distance between them)
	distancePercentPerFrame = 10;
}

//Private destructor
Camera::~Camera()
{
	//Not required
}
