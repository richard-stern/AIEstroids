// Author: Matin Kamali

#pragma once
#include "BaseState.h"
#include "Rect.h"
#include "String.h"
#include "Input.h"
#include "Renderer2D.h"
class StateMachine;

#define NUMBER_OF_BUTTONS 3 // this is terrible @incomplete

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
	struct Colour {
		Colour() {};
		Colour(float _r, float _g, float _b, float _a) {
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		};
		float r = 1.0f;  // white and opaque by default
		float g = 1.0f;
		float b = 1.0f;
		float a = 1.0f;
	};
	///
	struct Theme {
		Colour colour_normal;
		Colour colour_pressed;
		Colour colour_hover;

		aie::Font* font;
	};
	///
	struct Button {
		UI_STATES ui_state;
		Rect rect;
		String text;
		Theme theme;
		aie::EInputCodes keyboard_shortcut;
		void (*function)();	// <!> not freed by Button
	};
	///
	struct Panel {
		int at_y = 0;       // the place the next item should be drawn from
	};

	/// draw a button and return the state of the button
	void draw_button(const Button* button, aie::Renderer2D* renderer);
	/// draw a button inside of a panel. This way buttons can be arranged together
	void panel_push_button(Panel* panel, Button* button, aie::Renderer2D* renderer);
	/// get the default Theme
	Theme get_default_theme();
	/// update UI State based on input and mouse cursor
	void update_button_ui_state(Button* button, Vector2 mouse_cursor);
	/// get a default button <!> memory needs to be cleaned by the caller
	Button* new_button();
};


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

private:
	UI::Button* buttons[NUMBER_OF_BUTTONS];
	UI::Panel panel;
};

