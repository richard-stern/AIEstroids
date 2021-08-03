// Created by Cameron

#include "Level.h"

// Constructor - Spawn initial objects
Level::Level()
{
	// Get and store game window size
	aie::Application* application = aie::Application::GetInstance();
	windowW = (float)(application->GetWindowWidth());
	windowH = (float)(application->GetWindowHeight());

	// Create player
	float playerX = windowW * 0.5f;
	float playerY = windowH * 0.5f;
	m_player = new Player({ playerX, playerY });

	// Create stars
	// UNFINISHED - Stars don't exist yet
	for (int i = 0; i < STARS_COUNT; i++)
	{
		//m_starArray[i] = new Star({ (float)(rand() % (int)windowW), (float)(rand() % (int)windowH) });
	}

	// Create rocks
	// UNFINISHED - Rocks don't exist yet
	for (int i = 0; i < ROCKS_COUNT; i++)
	{
		// Keep getting a random position while the generated position is near player
		float spawnX, spawnY;
		do
		{
			spawnX = rand() % (int)windowW;
			spawnY = rand() % (int)windowH;
		} while (spawnX > (playerX - 10) && spawnX < (playerX + 10) && spawnY >(playerY - 10) && spawnY < (playerY + 10));

		// Create rock at the free position
		//m_rockArray[i] = new Rock({ spawnX, spawnY });
	}
}

// Destructor - Delete all objects
Level::~Level()
{
	// Delete stars
	for (int i = 0; i < STARS_COUNT; i++)
	{
		//delete m_starArray[i];
		//m_starArray[i] = nullptr;
	}

	// Delete rocks
	/*for (int i = 0; i < ROCKS_COUNT; i++)
	{
		delete m_rockArray[i];
		m_rockArray[i] = nullptr;
	}*/

	// Delete enemies
	for (int i = 0; i < m_enemyArray.Count(); i++)
	{
		delete m_enemyArray[i];
		m_enemyArray[i] = nullptr;
	}

	// Delete player
	delete m_player;
	m_player = nullptr;
}

// Update loop - Calls update on all objects
void Level::Update(float deltaTime)
{
	// Update player
	m_player->Update(deltaTime);

	// UNFINISHED - Enemies and Rocks don't exist yet
	// Update enemies
	for (int i = 0; i < m_enemyArray.Count(); i++)
		m_enemyArray[i]->Update(deltaTime);

	// Update rocks
	/*for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i]->Update();*/

	// Create enemy if timer is reached, and reset timer
	//enemyTimer -= deltaTime;
	//if (enemyTimer <= 0.0f)
	//{
	//	// Keep getting a random position while the generated position is colliding
	//	float spawnX, spawnY;
	//	do
	//	{
	//		spawnX = rand() % (int)windowW;
	//		spawnY = rand() % (int)windowH;
	//	} while (/* Colliding */);

	//	m_enemyArray.Add(new Enemy({ spawnX, spawnY })));

	//	enemyTimer = ENEMY_RATE;
	//}
}

// Draw loop - Calls draw on all objects
void Level::Draw(aie::Renderer2D* renderer)
{
	// Draw stars
	//for (int i = 0; i < STARS_COUNT; i++)
		//m_starArray[i]->Draw(renderer);

	// Draw player
	m_player->Draw(renderer);

	// Draw enemies
	for (int i = 0; i < m_enemyArray.Count(); i++)
		m_enemyArray[i]->Draw(renderer);

	// Draw all rocks
	/*for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i]->Draw(renderer);*/
}