// Author: Matin Kamali
#include "MenuState.h"
#include "Rect.h"
#include "String.h"
#include "Input.h"

  // -------------------------------------------
 //           DRAW UI FUNCTIONS
// -------------------------------------------
namespace UI { // @incomplete move UI into its own file?
	enum class UI_STATES {
		IDLE,
		HOVER,
		PRESSED,
	};
	///
	struct Button {
		Rect rect;
		String text;
		aie::Font* font;
		Input::EInputCodes keyboard_shrotcut;
	};
	///
	struct Panel {
		Rect rect;      // match items to the width OR the height of the panel based on Panel Mode
		int at_y;       // the place the next item should be drawn from
	};

	/// draw a button and return the state of the button
	UI_STATES draw_button(const Button* button, Vector2 mouse_cursor, aie::Renderer2D* renderer) {
		UI_STATES ui_state = UI_STATES::IDLE;
		aie::Input* input = aie::Input::GetInstance();

		{ // -- get UI state
			if (button->rect.is_point_inside(mouse_cursor.x, mouse_cursor.y)) {
				ui_state = UI_STATES::HOVER;
				// -- check for mouse click
				if (input->WasMouseButtonPressed(Input::EInputCodes::INPUT_MOUSE_BUTTON_LEFT)) {
					ui_state = UI_STATES::PRESSED;
				}
			};
			// -- keyboard shortcut
			if (input::WasKeyPressed(button->keyboard_shortcut)) {
					ui_state = UI_STATES::PRESSED;
			}
		}

		{ // -- draw button
			//@incomplete
		}
		return ui_state;
	};
	/// draw a button inside of a panel. This way buttons can be arranged together
	UI_STATES panel_push_button(Button* button, Vector2 mouse_cursor, aie::Renderer2D* renderer) {
		// remember to update button's rect
	};
};

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