// Author: Matin Kamali

#pragma once
#include "BaseState.h"

#include "Renderer2D.h"
class StateMachine;

class GameState : public BaseState {
public:
	GameState();
	/// Destroys the Level and GUI
	virtual ~GameState();

	/// Load and Initialise the Level and GUI
	void Enter() override;
	/// Update the Level
	void Update(float deltaTime, StateMachine* stateMachine) override;
	/// Calls Draw() on the Level. Calls the Draw() function on the GUI
	void Draw(aie::Renderer2D* renderer) override;
	/// Destroy the Level and GUI
	void Exit() override;
};

