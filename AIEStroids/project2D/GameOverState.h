#pragma once
#include "Renderer2D.h"
#include "StateMachine.h"
#include "BaseState.h"

class GameOverState : BaseState
{
public:
	GameOverState();
	~GameOverState();

	void Enter();
	void Update(float deltaTime, StateMachine* state);
	void Draw(aie::Renderer2D* renderer);
	void Exit();

private:
	// To be written...
};