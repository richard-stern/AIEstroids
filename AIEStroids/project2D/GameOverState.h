// Author: Cameron

#pragma once
#include "Renderer2D.h"
#include "Application.h"
#include "Input.h"
#include "Font.h"

#include "TextureManager.h"
#include "StateMachine.h"
#include "BaseState.h"

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
	const char strHeader[16] = "YOU DIED";
	const char strText[64] = "Press the Enter key to restart...";
	float posHeader;
	float posText;

	// Misc.
	aie::Renderer2D* renderer;
	bool animationComplete;
};