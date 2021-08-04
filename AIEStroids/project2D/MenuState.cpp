// Author: Matin Kamali
#include "MenuState.h"
#include "TextureManager.h"
#include "Application.h"
#include "StateMachine.h"
#include <iostream>
using namespace UI;
  // -------------------------------------------
 //               MENU STATE
// -------------------------------------------

///
MenuState::MenuState() {
	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
		buttons[i] = nullptr;
	};
};
///
MenuState::~MenuState() {
	Exit();
};
///
void MenuState::Enter() {
	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
		buttons[i] = new_button();
	};
	buttons[0]->text = "Play";
	buttons[1]->text = "Credits?";
	buttons[2]->text = "Exit";
};
///
void MenuState::Update(float deltaTime, StateMachine* stateMachine) {
	auto input = aie::Input::GetInstance();
	// -- keyboard shortcut
	if (input->WasKeyPressed(aie::INPUT_KEY_ENTER)) {
			stateMachine->ChangeState(StateMachine::ESTATE_GAME);
	}
};
///
void MenuState::Draw(aie::Renderer2D* renderer) {
	// // @incomplete remove this
	// panel.at_y = 0;

	// aie::Input* input = aie::Input::GetInstance();
	// Vector2 mouse_cursor;
	// mouse_cursor.x = input->GetMouseX();
	// mouse_cursor.y = input->GetMouseY();
	// printf("mouse: x: %f, y: %f\n", mouse_cursor.x, mouse_cursor.y);
	// int at_y = 320;
	// int at_x = 320;
	// for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) {
	// 	buttons[i]->rect.origin.x = at_x;
	// 	buttons[i]->rect.origin.y = at_y;
	// 	at_y += buttons[i]->rect.size.y;
	// 	update_button_ui_state(buttons[i], mouse_cursor);
	// 	draw_button(buttons[i], renderer);
	// };
	aie::Application* application = aie::Application::GetInstance();
	float width  = (float)(application->GetWindowWidth());
	float height = (float)(application->GetWindowHeight());
	
	auto font = TextureManager::Get()->LoadFont("..\\bin\\font\\consolas.ttf");
	renderer->DrawText2D(font, "AIESTROIDS", width * 0.5f - 22 * 4, height * 0.5f + 22);
	renderer->DrawText2D(font, "Press Enter", width * 0.5f - 23 * 4, height * 0.5f - 22);
};
///
void MenuState::Exit() {
	for (int i = 0; i < NUMBER_OF_BUTTONS; ++i) { // this is terrible but according to the document we should delete stuff in exit (which will be created again once back to menu)
		delete buttons[i];
		buttons[i] = nullptr;
	};
};

///
void UI::draw_button(const Button* button, aie::Renderer2D* renderer) {
		// -- change colour of button based on ui state
		Colour button_colour;
		switch (button->ui_state) {
			case UI_STATES::IDLE: {
				button_colour = button->theme.colour_normal;
			} break;
			case UI_STATES::HOVER: {
				button_colour = button->theme.colour_hover;
			} break;
			case UI_STATES::PRESSED: {
				button_colour = button->theme.colour_pressed;
			} break;
		};
		// -- set render colour
		renderer->SetRenderColour(button_colour.r, button_colour.g, button_colour.b, button_colour.a);
		// -- render button box
		renderer->DrawBox(button->rect.origin.x, button->rect.origin.y, button->rect.size.x, button->rect.size.y);
		// -- reset render colour to white
		renderer->SetRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
		// -- @incomplete draw text
		renderer->DrawText2D(button->theme.font, button->text.data, button->rect.origin.x, button->rect.origin.y);
};
///
void UI::panel_push_button(Panel* panel, Button* button, aie::Renderer2D* renderer) {
		// -- draw button
		draw_button(button, renderer);
		// -- move the cursor down by the button size
		panel->at_y += button->rect.size.y;
};
///
Theme UI::get_default_theme() {
	Theme theme;
	theme.colour_normal  = Colour(0.2, 0.2, 0.1, 1);
	theme.colour_pressed = Colour(0.1, 0.1, 0.1, 1);
	theme.colour_hover   = Colour(0.3, 0.3, 0.2, 1);
	
	theme.font = TextureManager::Get()->LoadFont("..\\bin\\font\\consolas.tff");

	return theme;
};
///
void UI::update_button_ui_state(Button* button, Vector2 mouse_cursor) {
	aie::Input* input = aie::Input::GetInstance();
	UI_STATES ui_state = UI_STATES::IDLE; // default
	
	if (button->rect.is_point_inside(mouse_cursor.x, mouse_cursor.y)) {
		ui_state = UI_STATES::HOVER;
		// -- check for mouse click
		if (input->WasMouseButtonPressed(aie::EInputCodes::INPUT_MOUSE_BUTTON_LEFT)) {
			ui_state = UI_STATES::PRESSED;
		}
	};
	// -- keyboard shortcut
	if (input->WasKeyPressed(button->keyboard_shortcut)) {
			ui_state = UI_STATES::PRESSED;
	}
};
///
Button* UI::new_button() {
	Button* button = new Button();
	button->rect.origin = Vector2();
	button->rect.size   = Vector2(240, 160); // default button size
	button->theme = get_default_theme();
	return button;
};