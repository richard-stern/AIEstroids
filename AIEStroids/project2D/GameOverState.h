// Created by Cameron

#pragma once
#include "Renderer2D.h"
#include "Application.h"
#include "Input.h"
#include "Font.h"

#include "TextureManager.h"
#include "StateMachine.h"
#include "BaseState.h"

/*
GameOverState Class

Presents a game over screen, and returns to the game state
upon pressing enter.

Contains a header (i.e. "Game Over!") and help text (i.e. "Enter to continue...").
*/

class GameOverState : public BaseState
{
public:
	GameOverState(aie::Renderer2D* renderer);
	~GameOverState();

	void Enter();
	void Update(float deltaTime, StateMachine* stateMachine);
	void Draw(aie::Renderer2D* renderer);
	void Exit();

private:
	// Window size
	float windowW;
	float windowH;

	// Fonts
	aie::Font* fontHeader;
	aie::Font* fontText;

	// Strings
	const char strHeader[16] = "GAME OVER!";
	const char strText[64] = "Press the Enter key to restart.";
	float posHeader;
	float posText;

	// Misc.
	aie::Renderer2D* renderer;
	bool animationComplete;
};