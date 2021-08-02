// Author: Matin kamali
#include "StateMachine.h"
#include "MenuState.h"
#include "GameState.h"
#include "GameOverState.h"
#include "Renderer2D.h"

///
StateMachine::StateMachine() {
	menu_state      = new MenuState();
	game_state      = new GameState();
	game_over_state = new GameOverState();
	current_state = menu_state;
};
///
StateMachine::~StateMachine() {
	delete menu_state;
	delete game_state;
	delete game_over_state;
};
///
void StateMachine::Update(float delta) {
	if (current_state) {
		current_state->Update(delta, this);
	};
};
///
void StateMachine::Draw(aie::Renderer2D* renderer) {
	if (current_state) {
		current_state->Draw(renderer);
	};
};
///
void StateMachine::ChangeState(int state) {
	// -- call Exit() on current state
	if (current_state) {
		current_state->Exit();
	}
	// -- change current state
	switch (state) {
		case ESTATE_MENU: {
			current_state = menu_state;
		} break;
		case ESTATE_GAME: {
			current_state = game_state;
		} break;
		case ESTATE_GAMEOVER: {
			current_state = game_over_state;
		} break;
	};
	// -- call Enter() on the new current state
	if (current_state) {
		current_state->Enter();
	}
};