#pragma once
#include "Renderer2D.h"
#include "Font.h"
#include "Input.h"
#include "Application.h"
	
class GUI
{
public:
	// GUI's creation
	static void Create();

	// Gui's destruction
	static void Destroy();

	// Returns the current instance
	static GUI* GetInstance();

	// Player setting health
	void SetHealth(int health);

	// Player setting score
	void SetScore(int score);

	// Player setting lives
	void SetLives(int lives);

	// Draws the Game UI
	void Draw(aie::Renderer2D* renderer, aie::Font* font,  aie::Input* input);

private:

	// Constructor
	GUI();

	// Destructor
	~GUI();

	// The current instance
	static GUI* m_Instance;

	// The Displayed health
	int m_Health;

	// The displayed score
	int m_Score;

	// The displayed lives
	int m_lives;
};

