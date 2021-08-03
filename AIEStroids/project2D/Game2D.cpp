#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Camera.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initialise 2D renderer and texture manager
	m_2dRenderer = new aie::Renderer2D();
	TextureManager::Create();

	// Initialise level (which initialises objects, cameras, etc.)
	m_pStateMachine = new StateMachine(m_2dRenderer);
}

Game2D::~Game2D()
{
	delete m_pStateMachine;

	// Delete 2D renderer and texture manager
	TextureManager::Destroy();
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

	// Update level
	m_pStateMachine->Update(deltaTime);
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	// Draw level
	m_pStateMachine->Draw(m_2dRenderer);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}