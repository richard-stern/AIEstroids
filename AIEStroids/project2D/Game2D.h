#pragma once

#include "Game.h"
#include "Renderer2D.h"
#include "Level.h"
#include "Enemy.h"
#include <vector>

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	aie::Renderer2D*	m_2dRenderer;
	Level* level;
	std::vector<Enemy*> enemies;
};