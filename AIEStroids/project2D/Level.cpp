// Author: Cameron

#include "Level.h"

// Constructor - Initializes level objects and systems
Level::Level(aie::Renderer2D* renderer)
{
	// Create Collision and GUI systems, setting game over to false
	CollisionManager::CreateInstance();
	GUI::Create();
	isGameOver = false;

	#pragma region Create Objects
	// Get game window size (for spawn positions)
	float windowW = (float)aie::Application::GetInstance()->GetWindowWidth();
	float windowH = (float)aie::Application::GetInstance()->GetWindowHeight();

	// Create Player at the window center
	m_player = new Player({ windowW * 0.5f, windowH * 0.5f });

	// Create Stars at random positions
	for (int i = 0; i < STARS_COUNT; i++)
		m_starArray[i] = new Star((float)(rand() % (int)(windowW * 2)), (float)(rand() % (int)(windowH * 2)));

	// Create Rocks (rocks automatically randomise position)
	for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i] = new Rock(m_player);
	#pragma endregion

	// Create Camera
	Camera::Create(renderer, m_player);
}

// Destructor - Deletes level objects and systems
Level::~Level()
{
	#pragma region Delete Objects
	// Delete Player
	delete m_player;
	m_player = nullptr;

	// Delete Stars
	for (int i = 0; i < STARS_COUNT; i++)
	{
		delete m_starArray[i];
		m_starArray[i] = nullptr;
	}

	// Delete Rocks
	for (int i = 0; i < ROCKS_COUNT; i++)
	{
		delete m_rockArray[i];
		m_rockArray[i] = nullptr;
	}

	// Delete Enemies
	for (int i = 0; i < m_enemyArray.Count(); i++)
	{
		delete m_enemyArray[i];
		m_enemyArray[i] = nullptr;
	}

	// Delete Health-Pickups
	for (int i = 0; i < m_healthArray.Count(); i++)
	{
		delete m_healthArray[i];
		m_healthArray[i] = nullptr;
	}
	#pragma endregion

	// Delete Collision, GUI and Camera systems
	CollisionManager::GetInstance()->DeleteInstance();
	GUI::Destroy();
	Camera::Destroy();
}

// Update loop - Runs update loop for all level objects and systems
void Level::Update(float deltaTime)
{
	#pragma region Update Objects
	// Update Player
	m_player->Update(deltaTime);

	// Update Stars
	for (int i = 0; i < STARS_COUNT; i++)
		m_starArray[i]->Update(deltaTime);

	// Update Rocks
	for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i]->Update(deltaTime);

	// Update Enemies
	for (int i = 0; i < m_enemyArray.Count(); i++)
	{
		m_enemyArray[i]->Update(deltaTime);
		if (m_enemyArray[i]->IsDestroyed())
		{
			delete m_enemyArray[i];
			m_enemyArray.RemoveAt(i);
		}
	}
		
	// Update Health-Pickups
	for (int i = 0; i < m_healthArray.Count(); i++)
		m_healthArray[i]->Update(deltaTime);
	#pragma endregion

	// Process Enemy and Health-Pickup timers
	// (creates Enemy/Health-Pickup whenever timer reaches 0, then resets timer)
	enemyTimer -= deltaTime;
	healthTimer -= deltaTime;
	if (enemyTimer <= 0.0f)
	{
		m_enemyArray.Add(new Enemy(m_player, m_rockArray));
		enemyTimer = ENEMY_RATE;
	}
	if (healthTimer <= 0.0f)
	{
		m_healthArray.Add(new HealthPickup(50));
		healthTimer = HEALTH_RATE;
	}

	#pragma region Update Object Transforms
	// Update Player and Health-Pickup Transforms
	m_player->UpdateTransforms();

	// Update Rocks Transforms
	for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i]->UpdateTransforms();

	// Update Enemies Transforms
	for (int i = 0; i < m_enemyArray.Count(); i++)
		m_enemyArray[i]->UpdateTransforms();

	// Update Health-Pickup Transforms
	for (int i = 0; i < m_healthArray.Count(); i++)
		m_healthArray[i]->UpdateTransforms();
	#pragma endregion

	// Update Collision system
	CollisionManager::GetInstance()->Update();

	#pragma region Re-update Object Transforms
	// Update Player Transforms
	m_player->UpdateTransforms();

	// Update Rocks Transforms
	for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i]->UpdateTransforms();

	// Update Enemies Transforms
	for (int i = 0; i < m_enemyArray.Count(); i++)
		m_enemyArray[i]->UpdateTransforms();

	// Update Health-Pickup Transforms
	for (int i = 0; i < m_healthArray.Count(); i++)
		m_healthArray[i]->UpdateTransforms();
	#pragma endregion

	// Update Camera system
	Camera::GetInstance()->Update(deltaTime);

	// Check if game is over
	if (m_player->GetLives() <= 0)
		isGameOver = true;
}

// Draw loop - Runs draw loop for all level objects
void Level::Draw(aie::Renderer2D* renderer)
{
	#pragma region Draw Objects
	// Draw Player
	m_player->Draw(renderer);

	// Draw Stars
	for (int i = 0; i < STARS_COUNT; i++)
		m_starArray[i]->Draw(renderer);

	// Draw Rocks
	for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i]->Draw(renderer);

	// Draw Enemies
	for (int i = 0; i < m_enemyArray.Count(); i++)
		m_enemyArray[i]->Draw(renderer);

	// Draw Health-Pickups
	for (int i = 0; i < m_healthArray.Count(); i++)
		m_healthArray[i]->Draw(renderer);
	#pragma endregion

	// Temporary - Draw debugging info
	CollisionManager::GetInstance()->DebugDraw(renderer);
}

// Returns whether the player has run out of lives
bool Level::IsGameOver()
{
	return isGameOver;
}