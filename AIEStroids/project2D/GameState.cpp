// Author: Matin Kamali
#include "GameState.h"
#include "GUI.h"
#include "Level.h"

/// init level and GUI to nullptr
GameState::GameState() {
	level = nullptr;
	gui   = nullptr;
};
/// Destory the level and GUI
GameState::~GameState() {
	delete level;
	// delete gui; // @incomplete gui is a singleton, we shouldn't be deleting it
};
/// Load and initialise the level and GUI
void GameState::Enter() {
	level = new Level();
	gui   = GUI::GetInstance();
};
///
void GameState::Update(float deltaTime, StateMachine* state) {
	// @incomplete check if the player's health is zero
	// if so, change state to game over state
	level->Update(deltaTime);
};
///
void GameState::Draw(aie::Renderer2D* renderer) {
	level->Draw(renderer);
	// @incomplete ask GUI.h to not take in input, it's a singleton and they should get it themselves
	aie::Input* input = aie::Input::GetInstance();
	// @incomplete ask GUI.h to not take in font, they should be handling the font and not the GameState
	auto font = TextureManager::Get()->LoadFont(""); // @incomplete pass a file path
	gui->Draw(renderer, font, input);
};
///
void GameState::Exit() {
	// @incomplete
};