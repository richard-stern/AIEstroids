#pragma once
#include "GameObject.h"
#include <vector>

class Enemy;
class Player;

class Level : GameObject
{
public:
	Level();
	~Level();

private:
	// To be written...
	Player* m_player;
	std::vector<Enemy*> m_enemies;

};