// Created by Cameron

#include "GameOverState.h"

// Constructor - Initializes internal variables
GameOverState::GameOverState(aie::Renderer2D* renderer)
{
	this->renderer = renderer;
	animationComplete = false;
}

// Destructor - Does nothing
GameOverState::~GameOverState()
{
}

// Called when state is entered - Initializes private variables
void GameOverState::Enter()
{
	// Reset camera scale for animation
	renderer->SetCameraScale(1.0f);
	animationComplete = false;

	// Get and store game window size
	aie::Application* application = aie::Application::GetInstance();
	windowW = (float)(application->GetWindowWidth());
	windowH = (float)(application->GetWindowHeight());

	// Load and store fonts to draw text with
	TextureManager* tm = TextureManager::Get();
	fontHeader = tm->LoadFont("..\\bin\\font\\times.ttf", 96);
	fontText = tm->LoadFont("..\\bin\\font\\consolas.ttf");

	// Calculate and store horizontal text positions to draw from (to center text)
	posHeader = (windowW * 0.5f) - (fontHeader->GetStringWidth(strHeader) * 0.5f);
	posText = (windowW * 0.5f) - (fontText->GetStringWidth(strText) * 0.5f);
}

// Update loop - Resets to game state when Enter is pressed
void GameOverState::Update(float deltaTime, StateMachine* stateMachine)
{
	// Process header animation and return if still in progress
	float cameraScale = renderer->GetCameraScale();
	if (!animationComplete)
	{
		cameraScale -= (0.05f * deltaTime);
		renderer->SetCameraScale(cameraScale);
		if (cameraScale <= 0.85)
		{
			animationComplete = true;
			renderer->SetCameraScale(1.0f);
		}

		return;
	}

	// If Enter is pressed, restart game (set state)
	if (aie::Input::GetInstance()->WasKeyPressed(aie::INPUT_KEY_ENTER))
		stateMachine->ChangeState(StateMachine::ESTATE_GAME);
}

// Draw loop - Draws the Game Over screen
void GameOverState::Draw(aie::Renderer2D* renderer)
{
	// Draw a black box over the screen
	renderer->SetRenderColour(0x000000FF);
	renderer->DrawBox(windowW * 0.5f, windowH * 0.5f, windowW, windowH, 0);

	// Draw text
	if (!animationComplete)
	{
		renderer->SetRenderColour(0xAA0000FF);
		renderer->DrawText2D(fontHeader, strHeader, posHeader, (windowH * 0.5f));
	}
	else
	{
		renderer->SetRenderColour(0xFFFFFFFF);
		renderer->DrawText2D(fontText, strText, posText, (windowH * 0.25f));
	}
	
	// Reset render colour to white
	renderer->SetRenderColour(0xFFFFFFFF);
}

// Called when state is exited - Resets camera scale
void GameOverState::Exit()
{
	renderer->SetCameraScale(1.0f);
}