// Created by Cameron

#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Application.h"

#include "DynamicArray.h"
#include "GameObject.h"
#include "Player.h"
//#include "Rock.h"		// Doesn't exist yet
//#include "Star.h"		// Doesn't exist yet
//#include "Enemy.h"	// Doesn't exist yet

#define ROCKS_COUNT		6		// Asteroids in the level
#define STARS_COUNT		100		// Stars in the level
#define ENEMY_RATE		6		// Seconds between enemy spawns

/*
Level Class

Stores the player, rocks, stars and enemies.
Calls update and draw on all objects each frame
*/

class Level : GameObject
{
public:
	Level();
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	// Window size
	float windowW;
	float windowH;

	// Objects
	Player* m_player;
	//Rock* m_rockArray[ROCKS_COUNT];		// Doesn't exist yet
	//Star* m_starArray[STARS_COUNT];		// Doesn't exist yet
	//DynamicArray<Enemy*> m_enemyArray();	// Doesn't exist yet

	// Misc.
	float enemyTimer = ENEMY_RATE;
};