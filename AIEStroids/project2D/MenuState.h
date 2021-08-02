// Author: Matin Kamali

#pragma once
#include "BaseState.h"

#include "Renderer2D.h"
class StateMachine;


class MenuState : public BaseState {
public:
	MenuState();
	virtual ~MenuState();

	/// Called when the state starts. Loads all the images needed for the menu. Inits everything
	void Enter() override;
	/// Process input and when the player has clicked the start button, you can start the game using pStatemachine->ChangeState(ESTATE_GAME);
	void Update(float deltaTime, StateMachine* stateMachine) override;
	/// Draw all the graphics for the menu
	void Draw(aie::Renderer2D* renderer) override;
	/// Called when the state is exited. Deletes all assets used in menu and cleans up everything
	void Exit() override;
};

