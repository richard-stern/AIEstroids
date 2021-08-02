#pragma once
#include "GameObject.h"
#include "Vector2.h"
#include "TextureManager.h"

class Star : GameObject
{
public:
	Star(float x, float y);
	~Star();

private:
	TextureManager* textureManager;

};

