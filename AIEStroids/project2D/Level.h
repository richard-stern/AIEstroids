// Author: Cameron

#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Application.h"

#include "DynamicArray.h"
#include "GameObject.h"
#include "Player.h"
#include "Rock.h"
#include "Star.h"
#include "Enemy.h"
#include "Camera.h"
#include "GUI.h"

#define ROCKS_COUNT		12				// Count of Rocks in the level
#define STARS_COUNT		100				// Count of Stars in the level
#define ENEMY_RATE		6				// Enemy spawn rate (sec between spawns)

class Level : GameObject
{
public:
	Level(aie::Renderer2D* renderer);
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	// Objects
	Player* m_player;					// Player object
	Rock* m_rockArray[ROCKS_COUNT];		// Static array of Rock objects
	Star* m_starArray[STARS_COUNT];		// Static array of Star objects
	DynamicArray<Enemy*> m_enemyArray;	// Dynamic array of Enemy objects

	// Misc.
	float enemyTimer = ENEMY_RATE;		// Countdown to spawn a new Enemy
};