// Author: Cameron

#pragma once
#include "Application.h"
#include "Renderer2D.h"

#include "DynamicArray.h"
#include "GameObject.h"
#include "Player.h"
#include "Rock.h"
#include "Star.h"
#include "Enemy.h"
#include "Camera.h"
#include "GUI.h"
#include "HealthPickup.h"

#define ROCKS_COUNT		24						// Count of Rocks in the level
#define STARS_COUNT		200						// Count of Stars in the level
#define ENEMY_RATE		6						// Enemy spawn rate (sec between spawns)
#define HEALTH_RATE		25						// Health-Pickup spawn rate (sec between spawns)

class Level : GameObject
{
public:
	Level(aie::Renderer2D* renderer);			// Constructor
	~Level();									// Destructor

	void Update(float deltaTime);				// Update loop
	void Draw(aie::Renderer2D* renderer);		// Draw loop
	bool IsGameOver();							// Returns if player has lives or not

private:
	// Objects
	Player* m_player;							// Player object
	Rock* m_rockArray[ROCKS_COUNT];				// Array of Rock objects
	Star* m_starArray[STARS_COUNT];				// Array of Star objects
	DynamicArray<Enemy*> m_enemyArray;			// Dynamic array of Enemy objects
	DynamicArray<HealthPickup*> m_healthArray;	// Health-Pickup object
	
	// Misc.
	float enemyTimer = ENEMY_RATE;				// Countdown to spawn a new Enemy
	float healthTimer = HEALTH_RATE;			// Countdown to spawn a new Health-Pickup
	bool isGameOver;							// Whether the player's has lives or not
};