// Created by Cameron

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
	Level(aie::Renderer2D* renderer);
	~Level();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);
	//Actor** GetRocks() { return (Actor**) m_rockArray; }		// I didn't write these
	//Player* GetPlayer() { return m_player; }					// "

private:
	// Window size
	float windowW;
	float windowH;

	// Objects
	Player* m_player;
	//Rock* m_rockArray[ROCKS_COUNT];			// UNFINISHED - Rocks don't exist yet
	Star* m_starArray[STARS_COUNT];	
	DynamicArray<Enemy*> m_enemyArray;

	// Misc.
	float enemyTimer = ENEMY_RATE;
};