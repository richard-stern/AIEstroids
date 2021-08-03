#include "Star.h"
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

	GameObject::m_WrapAndRespawn = true;
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
}

void Star::Draw(aie::Renderer2D* _renderer)
{
	float brightness = (sin(totalDeltaTime * flashSpeed) + 1.0f) / 4.0f;
	_renderer->SetRenderColour(brightness, brightness, brightness, 1.0f);

	//Draw the sprite if the texture is loaded
	if (m_Texture != nullptr)
	{
		Vector2 position = GetPosition();
		_renderer->DrawSprite(m_Texture, position.x, position.y, 1.0f, 1.0f);
	}
	else
	{
		Vector2 position = GetLocalPosition();
		_renderer->DrawCircle(position.x, position.y, 1.0f, 0.1f);
	}

	_renderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
}
