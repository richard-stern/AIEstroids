// Created by Cameron

#include "GameOverState.h"

// Constructor - Does nothing
GameOverState::GameOverState()
{
}

// Destructor - Does nothing
GameOverState::~GameOverState()
{
}

// Called when state is entered - Initializes private variables
void GameOverState::Enter()
{
	// Get and store game window size
	aie::Application* application = aie::Application::GetInstance();
	windowW = (float)(application->GetWindowWidth());
	windowH = (float)(application->GetWindowHeight());

	// Load and store fonts to draw text with
	TextureManager* tm = TextureManager::Get();
	fontHeader = tm->LoadFont("bin/font/consolas.ttf", 46);
	fontText = tm->LoadFont("./font/consolas.ttf", 20);

	// Calculate and store horizontal text positions to draw from (to center text)
	posHeader = (windowW * 0.5f) - (fontHeader->GetStringWidth(strHeader) * 0.5f);
	posText = (windowW * 0.5f) - (fontHeader->GetStringWidth(strText) * 0.5f);
}

// Update loop - Resets to game state when Enter is pressed
void GameOverState::Update(float deltaTime, StateMachine* stateMachine)
{
	// If Enter is pressed, restart game (set state)
	if (aie::Input::GetInstance()->WasKeyPressed(aie::INPUT_KEY_ENTER))
		stateMachine->ChangeState(ESTATE_GAME);
}

// Draw loop - Draws the Game Over screen
void GameOverState::Draw(aie::Renderer2D* renderer)
{
	// Draw a black box over the screen
	renderer->SetRenderColour(0x000000FF);
	renderer->DrawBox(windowW * 0.5f, windowH * 0.5f, windowW, windowH, 0);

	// Draw text
	renderer->SetRenderColour(0xAA0000FF);
	renderer->DrawText2D(fontHeader, strHeader, posHeader, (windowH * 0.5f));
	renderer->SetRenderColour(0xFFFFFFFF);
	renderer->DrawText2D(fontText, strText, posText, (windowH * 0.25f));

	// Reset render colour to white
	renderer->SetRenderColour(0xFFFFFFFF);
}

// Called when state is exited - Does nothing
void GameOverState::Exit()
{
}