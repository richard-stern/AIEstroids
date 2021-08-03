#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Camera.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	//Did this so we could actually see
	//-------------------------------------/
	//		Singleton Initialisation
	//___________________________________/
	TextureManager::Get();

	level = new Level();

	//Create the camera controller
	Camera::Create(m_2dRenderer, level->GetPlayer());
}

Game2D::~Game2D()
{
	for (Enemy* enemy : enemies)
	{
		delete enemy;
		enemies.clear();
	}

	delete level;

	TextureManager::Destroy();
	Camera::Destroy();

	// Delete the renderer.
	delete m_2dRenderer;
}

void Game2D::Update(float deltaTime)
{
	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}

	//Temporary
	level->GetPlayer()->Update(aie::Application::GetInstance()->GetDeltaTime());
	level->GetPlayer()->GetPhysicsBody()->Update();

	//Call update on the camera
	Camera::GetInstance()->Update(deltaTime);
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	//Temporary so we can see tha player
	level->GetPlayer()->Draw(m_2dRenderer);

	for (Enemy* enemy : enemies)
	{
		enemy->Draw(m_2dRenderer);
	}
	//Stars block it from drawing for now
	//level->Draw(m_2dRenderer);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}