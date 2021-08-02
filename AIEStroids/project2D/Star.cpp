#include "Star.h"

Star::Star(float x, float y)
{
	//Set position
	Vector2 position;
	position.x = x;
	position.y = y;
	SetLocalPosition(position);

	//Texture
	textureManager = TextureManager::Get();

			//m_Texture = textureManager->LoadTexture("[TEXTURE NAME]");
}

Star::~Star()
{
	//Not required
}

void Star::Update(float deltaTime)
{
	//Does nothing
}

void Star::Draw(aie::Renderer2D* _renderer)
{
	//Draw the sprite if the texture is loaded
	if (m_Texture != nullptr)
	{
		Vector2 position = GetLocalPosition();
		_renderer->DrawSprite(m_Texture, position.x, position.y, 1.0f, 1.0f);
	}
}
