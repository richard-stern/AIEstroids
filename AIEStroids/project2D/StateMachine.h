// Author: Matin kamali

#pragma once

class Renderer2D;

// A finite state machine to control the overall game flow.
// • Is created by Application2D.
// • Creates MenuState, GameState and GameOverState.

class StateMachine {
public:
	enum class STATES {	// usecase: STATES::ESTATE_MENU / StateMchine::STATES::ESTATE_MENU
		ESTATE_MENU,
		ESTATE_GAME,
		ESTATE_GAMEOVER
	};

	StateMachine();
	~StateMachine();

	/// Calls Update() on the active state
	void Update(float deltaTime);
	/// Calls Draw() on the active state
	void Draw(Renderer2D* renderer);
	/// Change to the specified state
	void ChangeState(STATES state);
};

