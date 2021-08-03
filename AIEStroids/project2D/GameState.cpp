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
	Exit(); // @incomplete why are we exiting twice? As in we can call Exit() and then delete game_state
};
/// Load and initialise the level and GUI
void GameState::Enter() {
	level = new Level();
	GUI::Create(); // @incomplete fix this shit
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
	aie::Input* input = aie::Input::GetInstance();
	auto font = TextureManager::Get()->LoadFont("font\\consolas.ttf"); // @incomplete ask Jaden to have a bunch of #define s that point to fonts and textures that we have
	gui->Draw(renderer, font, input);
};
///
void GameState::Exit() {
	delete level;
	// delete gui; // @incomplete gui is a singleton, we shouldn't be deleting it
	level = nullptr;
	gui   = nullptr;
};