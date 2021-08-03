// Author: Cameron

#include "Level.h"

// Constructor - Initializes level objects and systems
Level::Level(aie::Renderer2D* renderer)
{
	// Create Collision and GUI systems
	CollisionManager::CreateInstance();
	GUI::Create();

	#pragma region Create Objects
	// Get game window size (for spawn positions)
	float windowW = (float)aie::Application::GetInstance()->GetWindowWidth();
	float windowH = (float)aie::Application::GetInstance()->GetWindowHeight();

	// Create Player at the window center
	m_player = new Player({ windowW * 0.5f, windowH * 0.5f });

	// Create Stars at random positions
	for (int i = 0; i < STARS_COUNT; i++)
		m_starArray[i] = new Star((float)(rand() % (int)windowW), (float)(rand() % (int)windowH));

	// Create Rocks (rocks automatically randomise position)
	for (int i = 0; i < ROCKS_COUNT; i++)
		m_rockArray[i] = new Rock();
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
	#pragma endregion

	// Delete Collision, GUI and Camera systems
	// UNFINISHED - Should I delete GUI here?
	CollisionManager::GetInstance()->DeleteInstance();
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
		m_enemyArray[i]->Update(deltaTime);
	#pragma endregion

	// Process Enemy timer (creates Enemy whenever timer reaches 0, then resets timer)
	enemyTimer -= deltaTime;
	if (enemyTimer <= 0.0f)
	{
		m_enemyArray.Add(new Enemy(m_player, m_rockArray));
		enemyTimer = ENEMY_RATE;
	}

	// Update Collision and Camera systems
	CollisionManager::GetInstance()->Update();
	Camera::GetInstance()->Update(deltaTime);
}

// Draw loop - Runs draw loop for all level objects
void Level::Draw(aie::Renderer2D* renderer)
{
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
}