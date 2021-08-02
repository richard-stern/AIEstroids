#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "TextureManager.h"

class Star : GameObject
{
public:
	Star(float x, float y);
	~Star();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* _renderer);

private:
	TextureManager* textureManager;



};

