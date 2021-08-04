#include "Star.h"
#include "Camera.h"
#include <time.h>
#include <chrono>

Star::Star(float x, float y)
{
	//Set position
	Vector2 position;
	position.x = x;
	position.y = y;
	SetPosition(position);

	//Texture
	textureManager = TextureManager::Get();

	m_Texture = nullptr;
	//m_Texture = textureManager->LoadTexture("[TEXTURE NAME]");

	GameObject::m_WrapAndRespawn = true; //Functionality handled by me in Update() instead
	totalDeltaTime = 0.0f;
	flashSpeed = (float)(rand() % 314159) / 10000.0f;
}

Star::~Star()
{
	//Not required
}

void Star::Update(float deltaTime)
{
	totalDeltaTime += deltaTime;

	//Wrap object
	Vector2 cameraPosition = Camera::GetInstance()->GetPosition();
	Vector2 screenSize;
	screenSize.x = aie::Application::GetInstance()->GetWindowWidth();
	screenSize.y = aie::Application::GetInstance()->GetWindowHeight();

	#pragma region Screen Wrapping

	//If the object is too far left
	if (GetPosition().x < cameraPosition.x)
	{
		Vector2 newPosition;
		newPosition.x = GetPosition().x + (screenSize.x * 2);
		newPosition.y = GetPosition().y;
		SetPosition(newPosition);
	}

	//If the object is too far right
	if (GetPosition().x > cameraPosition.x + (screenSize.x))
	{
		Vector2 newPosition;
		newPosition.x = GetPosition().x - (screenSize.x * 2);
		newPosition.y = GetPosition().y;
		SetPosition(newPosition);
	}

	//If the object is too far down
	if (GetPosition().y < cameraPosition.y)
	{
		Vector2 newPosition;
		newPosition.x = GetPosition().x;
		newPosition.y = GetPosition().y + (screenSize.y * 2);
		SetPosition(newPosition);
	}

	//If the object is too far up
	if (GetPosition().y > cameraPosition.y + (screenSize.y))
	{
		Vector2 newPosition;
		newPosition.x = GetPosition().x;
		newPosition.y = GetPosition().y - (screenSize.y * 2);
		SetPosition(newPosition);
	}

	#pragma endregion
}

void Star::Draw(aie::Renderer2D* _renderer)
{
	float brightness = (sin(totalDeltaTime * flashSpeed) + 1.0f) / 4.0f;
	_renderer->SetRenderColour(brightness, brightness, brightness, 1.0f);

	//Draw the sprite if the texture is loaded
	if (m_Texture != nullptr)
	{
		Vector2 position = GetPosition();
		_renderer->DrawSprite(m_Texture, position.x, position.y, flashSpeed / 2.0f, flashSpeed / 2.0f);
	}
	else
	{
		Vector2 position = GetPosition();
		_renderer->DrawCircle(position.x, position.y, flashSpeed / 2.0f, flashSpeed / 2.0f);
	}

	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
}
