// Author: Matin Kamali
#include "MenuState.h"

using namespace UI;
  // -------------------------------------------
 //               MENU STATE
// -------------------------------------------

///
MenuState::MenuState() {
	// @incomplete
};
///
MenuState::~MenuState() {
	// @incomplete
};
///
void MenuState::Enter() {
	// @incomplete
};
///
void MenuState::Update(float deltaTime, StateMachine* stateMachine) {
	// @incomplete
};

///
void MenuState::Draw(aie::Renderer2D* renderer) {
	// @incomplete
};
///
void MenuState::Exit() {
	// @incomplete
};

///
UI_STATES draw_button(const Button* button, Vector2 mouse_cursor, aie::Renderer2D* renderer) {
		UI_STATES ui_state = UI_STATES::IDLE;
		aie::Input* input = aie::Input::GetInstance();

		{ // -- get UI state
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
		}

		{ // -- draw button
			//@incomplete
		}
		return ui_state;
};
///
UI_STATES panel_push_button(Button* button, Vector2 mouse_cursor, aie::Renderer2D* renderer) {
		// remember to update button's rect
		return UI_STATES::IDLE;
};
///
Theme get_default_theme() {
	Theme theme;
	theme.colour_normal  = Colour(0.2, 0.2, 0.1, 1);
	theme.colour_pressed = Colour(0.1, 0.1, 0.1, 1);
	theme.colour_hover   = Colour(0.3, 0.3, 0.2, 1);
	// @incomplete get a default font
	return theme;
};