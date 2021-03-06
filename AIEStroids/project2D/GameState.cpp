// Author: Matin Kamali
#include "GameState.h"
#include "GUI.h"
#include "Level.h"

/// init level and GUI to nullptr
GameState::GameState(aie::Renderer2D* _renderer) {
	level = nullptr;
	gui   = nullptr;
	renderer = _renderer;
};
/// Destory the level and GUI
GameState::~GameState() {
	Exit(); // @incomplete why are we exiting twice? As in we can call Exit() and then delete game_state
};
/// Load and initialise the level and GUI
void GameState::Enter() {
	level = new Level(renderer);
	gui   = GUI::GetInstance();
};
///
void GameState::Update(float deltaTime, StateMachine* state) {
	// @incomplete check if the player's health is zero
	// if so, change state to game over state
	level->Update(deltaTime);
	if (level->IsGameOver())
        state->ChangeState(StateMachine::ESTATE_GAMEOVER);
};
///
void GameState::Draw(aie::Renderer2D* renderer) {
	level->Draw(renderer);
	aie::Input* input = aie::Input::GetInstance();
	auto font = TextureManager::Get()->LoadFont("..\\bin\\font\\consolas.ttf"); // @incomplete ask Jaden to have a bunch of #define s that point to fonts and textures that we have
	gui->Draw(renderer, font, input);
};
///
void GameState::Exit() {
	delete level;
	// delete gui; // @incomplete gui is a singleton, we shouldn't be deleting it
	level = nullptr;
	gui   = nullptr;
};