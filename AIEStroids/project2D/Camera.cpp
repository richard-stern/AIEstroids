#include "Camera.h"
#include "Renderer2D.h"
#include <cmath>
#include <iostream>

#define PI 3.14159265359

//Singleton initialisation
Camera* Camera::instance = nullptr;

#pragma region Singleton Functions

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

//Private constructor
Camera::Camera()
{
	//Starting position of camera
	cameraPosition.x = 0.0f;
	cameraPosition.y = 0.0f;

	//The minimum absolute distance moved by the camera while smoothing, anything less is cut off and the camera doesn't move
	minMoveDistance = 0.25f;

	//How far the camera moves towards its target per second (based on a percentage of the distance between them)
	followSpeed = 250;

	renderer = nullptr;
	player = nullptr;

	//Shake settings
	shakeDuration = 0.0f;
	shakeTimer = 0.0f;
	shakeStrength = 0;

	//Assign application
	application = aie::Application::GetInstance();
}

//Private destructor
Camera::~Camera()
{
	//Not required
}

#pragma endregion

#pragma region Position Functions

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

#pragma endregion

//Update is called once per frame
void Camera::Update(float deltaTime)
{
	#pragma region Smooth Follow 

	//Get the player's position
	Vector2 playerPosition;
	playerPosition = player->GetGlobalPosition();

	//Find the distance between the camera and the player
	Vector2 offsetBaseCameraPosition = cameraPosition;
	offsetBaseCameraPosition.x = offsetBaseCameraPosition.x + application->GetWindowWidth() / 2;
	offsetBaseCameraPosition.y = offsetBaseCameraPosition.y + application->GetWindowHeight() / 2;
	Vector2 distance = (playerPosition - offsetBaseCameraPosition);

	//If the distance is significant enough to warrant moving the camera
	if (abs(distance.GetMagnitude()) * (followSpeed / 100.0f) * deltaTime > minMoveDistance)
	{
		//Move the camera toward the player by the distance fraction
		cameraPosition += (distance * (followSpeed / 100.0f) * deltaTime);
	}

	#pragma endregion

	#pragma region Screenshake

	Vector2 shakenPosition;
	shakenPosition.x = cameraPosition.x;
	shakenPosition.y = cameraPosition.y;

	//If the camera should be shaking currently
	if (shakeTimer > 0.0f)
	{
		//Projects a circle around the base position of the camera and chooses a random point in that circle, finds the offset and applies it to the final position each frame
		//Circle radius is determined by strength value and duration is the value given to timer at the start of the shake
		//Once timer has ended, the offset is set to 0 and the camera defaults back to its base position

		float angle = rand() % 360; //Chooses a random angle, then determines magnitude of vector using strength parameter
		Vector2 shakeOffset; //The vector which is added to the shakenPosition to create the final product for this frame

		//The ratio between the x and y of the vector
		float ratio = 0.0f;
		
		//Will tan() return undefined?
		if (angle != 270 && angle != 90)
		{
			//The angle is within a valid domain for tan()
			ratio = tan(angle * (PI / 180.0f));

			shakeOffset.x = 1;
			shakeOffset.y = ratio;
		}
		else
		{
			//Treat the theoretical tan() as infinity degrees by making x = 0
			shakeOffset.x = 0.0f;
			shakeOffset.y = 1.0f;
		}

		//Set maximum magnitude of the vector
		shakeOffset = shakeOffset.GetNormalised();

		//Randomise distance along normalised vector
		shakeOffset *= shakeStrength * (float)((rand() % 1000) / 1000.0f);

		//All possible vectors will only be in 1st and 4th quadrant, flip the vector if angle is between 90 and 270
		if (angle > 90 && angle < 270)
		{
			shakeOffset.x *= -1;
			shakeOffset.y *= -1;
		}

		//Add to final vector
		shakenPosition += shakeOffset;

		//If the shake has ended
		if (shakeTimer <= 0.0f)
		{
			shakeStrength = 0;
			shakeDuration = 0.0f;
			shakeTimer = 0.0f;

			//Set camera back to default
			shakenPosition.x = cameraPosition.x;
			shakenPosition.y = cameraPosition.y;
		}
		else
		{
			//Decrement the timer
			shakeTimer -= deltaTime;
		}
	}

	#pragma endregion

	//Apply the Vector2 to the renderer's camera
	renderer->SetCameraPos(shakenPosition.x, shakenPosition.y);
}

//Called to initialise a screenshake, if duration is set to 0, the shake is force-stopped
void Camera::Shake(float strength, float duration)
{
	shakeDuration = abs(duration);
	shakeTimer = shakeDuration; //Counts down using deltaTime until below 0

	shakeStrength = abs(strength); //The max distance the camera is set from it's base position each frame of the shake
}