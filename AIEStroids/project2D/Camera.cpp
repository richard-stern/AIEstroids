#include "Camera.h"

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
	this->position.x = position.x;
	this->position.y = position.y;
}

//Set camera postion using 2 floats
void Camera::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

//Returns the Vector2 position of the camera
Vector2 Camera::GetPosition()
{
	return position;
}

void Camera::Update(float deltaTime)
{
	//Get the player's position

	//Smoothing and stuff

	//Screenshake?
}

//Private constructor
Camera::Camera()
{

}

//Private destructor
Camera::~Camera()
{

}
